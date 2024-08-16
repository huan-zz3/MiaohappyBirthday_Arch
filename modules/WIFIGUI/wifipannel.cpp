#include "wifipannel.h"
#include "ui_wifipannel.h"

WIFIPannel::WIFIPannel(QWidget *parent) :
    IWIFIGUI(parent),
    ui(new Ui::WIFIPannel)
{
    ui->setupUi(this);
//    this->setCursor(Qt::BlankCursor);
//    initList();
    initTable();
    initButton();
//    showFullScreen();
}

WIFIPannel::~WIFIPannel()
{
    delete ui;
}
void WIFIPannel::setWIFIControl(IWIFIControl *_wfc){
    wfc = _wfc;
}
void WIFIPannel::showWIFIPanel(){
    showFullScreen();
}
void WIFIPannel::closeWIFIPanel(){
    hide();
}
void WIFIPannel::initTable(){
    //在 widget 窗口中添加一个 4 行 3 列的表格
    tablewidget = new QTableWidget(40,2,this);
    //自定义表格的尺寸和字体大小
//    tablewidget->resize(900,350);
    QString itemFont = loadFont(":/font/src/font/321impact.ttf");
    const int fontsize = 15;
    tablewidget->setGeometry(200,100,624,400);
    tablewidget->setFont(QFont(itemFont, fontsize));
    //设置表格中每一行的表头
    item_ssid = new QTableWidgetItem("SSID");
    item_signalLevel = new QTableWidgetItem("SignalLevel");
    tablewidget->setHorizontalHeaderItem(0, item_ssid);
    tablewidget->setHorizontalHeaderItem(1, item_signalLevel);
    //设置表格数据区内的所有单元格都不允许编辑
    tablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QObject::connect(tablewidget, &QTableWidget::itemClicked, [](QTableWidgetItem *item) {
        qDebug() << "Item clicked:" << item->text();
    });
    // 设置列固定宽度
    tablewidget->setColumnWidth(0, 500);
    tablewidget->setColumnWidth(1, 100);
    // 隐藏序号列
    tablewidget->verticalHeader()->setVisible(false);
    // 单元格双击连接该wifi
    connect(tablewidget, &QTableWidget::itemDoubleClicked, this, &WIFIPannel::slot_connectThiswifi);
//    connect(tablewidget, &QTableWidget::itemDoubleClicked, this, [this]() {
        
//    });
    
}
void WIFIPannel::addWIFIItem()
{
    // 清空之前的测试项（如果有的话）
    auto wifiDataList = wfc->getWIFIlist();
//    listwidget->clear();
    
    QString itemFont = loadFont(":/font/src/font/Bock-Medium.ttf");
    const int fontsize = 20;
    
    for(int i = 0; i < wifiDataList.size(); ++i) {
        const QMap<QString, QString>& wifiInfo = wifiDataList.at(i);
        
        // 从QMap中提取SSID和SignalLevel
        QString ssid = wifiInfo.value("ssid");
        QString signalLevel = wifiInfo.value("signal level");
        
        // 创建新的列表项并设置文本
        QTableWidgetItem *_item_ssid = new QTableWidgetItem(ssid);
        QTableWidgetItem *_item_signallevel = new QTableWidgetItem(signalLevel);
//        QListWidgetItem *item_singlewifi = new QListWidgetItem(ssid + " ---- " + signalLevel);
//        QListWidgetItem *item_ssid = new QListWidgetItem(ssid);
//        QListWidgetItem *item_signalLevel = new QListWidgetItem(signalLevel);
        
        // 设置样式
//        item_singlewifi->setTextAlignment(Qt::AlignCenter);
        _item_ssid->setTextAlignment(Qt::AlignCenter);
        _item_signallevel->setTextAlignment(Qt::AlignCenter);
//        item_singlewifi->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
//        item_singlewifi->setFont(QFont(itemFont, fontsize));
        
//        item_signalLevel->setTextAlignment(Qt::AlignCenter);
//        item_signalLevel->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
//        item_signalLevel->setFont(QFont(itemFont, fontsize));
        
        // 添加到列表中
        tablewidget->setItem(i,0,_item_ssid);
        tablewidget->setItem(i,1,_item_signallevel);
//        listwidget->addItem(item_singlewifi);
        // 同样的，关于如何处理SignalLevel，请根据实际需求调整
//        listwidget->addItem(item_signalLevel); 
        
        // 如果需要在同一行显示SSID和SignalLevel，请考虑使用自定义项或调整UI设计
    }
}
QString WIFIPannel::loadFont(QString fontpath){
    int fontId = QFontDatabase::addApplicationFont(fontpath);
    if (fontId == -1) {
        qDebug() << "Failed to load custom font.";
        return "";
    }
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if (fontFamilies.isEmpty()) {
        qDebug() << "No font family found for the loaded font.";
        return "";
    }
    const QString &fontName = fontFamilies.at(0);
    return fontName;
}
void WIFIPannel::slot_connectThiswifi(QTableWidgetItem *clickeditem){
    WifiPasswordDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) { // 用户点击了确认
        QString password = dialog.getPassword();
        qDebug() << "密码：" << password;
        QString ssid;
        if(tablewidget->column(clickeditem)==0){
            ssid = clickeditem->text();
        }else{
            ssid = tablewidget->item(tablewidget->column(clickeditem), 0)->text();
        }
        qDebug() << ssid + "+" + password;
        
        if(wfc->connectWIFI(ssid,password)){
            qDebug()<<"wifi connect success!";
        }
        
    } else { // 用户点击了取消
        qDebug() << "用户取消输入";
    }
}
void WIFIPannel::initButton(){
    backbutton = new QPushButton("Back to Home",this);
    backbutton->setGeometry(850, 500, 100, 50);
    
    connect(backbutton, &QPushButton::clicked, this, [this](){
        this->closeWIFIPanel();
    });
    
}
