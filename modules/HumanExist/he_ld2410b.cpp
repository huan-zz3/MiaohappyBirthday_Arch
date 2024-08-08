#include "he_ld2410b.h"

HE_LD2410B::HE_LD2410B(QObject *parent):IHumanExist(parent)
{
    eh_ = new ExistenceofHumanBody(INTERRUPT_GPIO, this);
    QThread *serviceThread = new QThread;
    eh_->moveToThread(serviceThread);
    
    connect(serviceThread, &QThread::started, eh_, &ExistenceofHumanBody::slot_onThreadStarted);
    connect(serviceThread, &QThread::finished, eh_, &QObject::deleteLater, Qt::QueuedConnection);
    connect(serviceThread, &QThread::finished, serviceThread, &QObject::deleteLater, Qt::QueuedConnection);
    
    serviceThread->start(); // 启动线程
    
}

/**************************************/
ExistenceofHumanBody::ExistenceofHumanBody(int _line, IHumanExist *parent) : QObject(parent), IHparent_(parent), line(_line)
{}
void ExistenceofHumanBody::slot_onThreadStarted(){
    gpioInit(line);
}

void ExistenceofHumanBody::gpioInit(int linenum){
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    struct gpiod_line_event event;
    int error;
    
    // 打开gpiochip0设备
    chip = gpiod_chip_open_by_name("gpiochip0");
    if (!chip) {
        qWarning()<<"Opening gpiochip0 failed";
        return;
    }

    // 获取第linenum个引脚（编号从0开始）
    line = gpiod_chip_get_line(chip, linenum);
    if (!line) {
        qWarning()<<"Getting line failed";
        goto out_close_chip;
    }

    // 请求引脚为输入模式，并监听双向沿
    error = gpiod_line_request_both_edges_events(line, "MiaohappyBirthday");
    if (error < 0) {
        qWarning()<<"Requesting events failed";
        goto out_release_line;
    }

    qDebug()<<"Waiting for events...";
    
        // 等待事件并处理
    while (1) {
        error = gpiod_line_event_wait(line, NULL);
        if (error < 0) {
            qWarning()<<"Wait for GPIO event failed";
            break;
        } else if (error == 0) {
            qDebug()<<"No event occurred within timeout";
            continue;
        }
        
        // 读取事件
        error = gpiod_line_event_read(line, &event);
        if (error < 0) {
            qWarning()<<"Read GPIO event failed";
            break;
        }
        
        // 处理事件
        handle_event(&event);
    }
    
out_release_line:
    gpiod_line_release(line);
out_close_chip:
    gpiod_chip_close(chip);
    
    return;
}

void ExistenceofHumanBody::handle_event(struct gpiod_line_event *event){
        if (event->event_type == GPIOD_LINE_EVENT_RISING_EDGE) {
            qDebug()<<"Rising edge detected";
//            emit signal_pinEdgeChange(1);
            emit IHparent_->signal_HumanExist();
        } else if (event->event_type == GPIOD_LINE_EVENT_FALLING_EDGE) {
            qDebug()<<"Falling edge detected";
//            emit signal_pinEdgeChange(2);
            emit IHparent_->signal_HumanNotExist();
        }
    }
