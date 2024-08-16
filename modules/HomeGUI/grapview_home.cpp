#include "grapview_home.h"

GrapView_home::GrapView_home(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    slideValid = true;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, [this](){
        timer->stop();
        slideValid = true;
    });
//    this->setCursor(Qt::BlankCursor);
}
void GrapView_home::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton) { 
        int deltaY = event->pos().y() - lastMousePos.y();
        if(slideValid){
            if (deltaY > SLIDE_DISTANCE) {
//                qDebug() << "向下滑动";
//                emit signal_slideToBottom();
                slideValid = false;
                timer->start(SLIDE_WAITIME);
            } else if (deltaY < -SLIDE_DISTANCE) {
//                qDebug() << "向上滑动";
//                emit signal_slideToTop();
                slideValid = false;
                timer->start(SLIDE_WAITIME);
            }
        }
        // 更新lastMousePos以供下一次比较
        lastMousePos = event->pos();
    }
    QGraphicsView::mouseMoveEvent(event);
}
void GrapView_home::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        lastMousePos = event->pos(); // 记录鼠标按下时的位置
//        if (QGraphicsItem *item = itemAt(event->pos())) {
//            qDebug() << "You clicked on item" << item;
//        } else {
//            qDebug("You didn't click on an item.");
//        }
    }
    QGraphicsView::mousePressEvent(event);
}
