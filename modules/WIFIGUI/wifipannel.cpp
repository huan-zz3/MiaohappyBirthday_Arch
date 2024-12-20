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
void WIFIPannel::setDefaultWIFI(){
    initdefaultWIFI();
}
void WIFIPannel::setWIFIControl(IWIFIControl *_wfc){
    wfc = _wfc;
}
void WIFIPannel::showWIFIPanel(){
    showFullScreen();
    this->addWIFIItem();
}
void WIFIPannel::closeWIFIPanel(){
    hide();
}
void WIFIPannel::initTable(){
    //在 widget 窗口中添加一个 50 行 2 列的表格
    tablewidget = new QTableWidget(50,2,this);
    //自定义表格的尺寸和字体大小
//    tablewidget->resize(900,350);
    QString itemFont = loadFont(":/font/src/font/Rainbow-Party.ttf");
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
    
}
void WIFIPannel::addWIFIItem()
{
    // 清空之前的测试项（如果有的话）
    auto wifiDataList = wfc->getWIFIlist();
    
    tablewidget->setRowCount(wifiDataList.size());
    for(int i = 0; i < wifiDataList.size(); ++i) {
        const QMap<QString, QString>& wifiInfo = wifiDataList.at(i);
        
        // 从QMap中提取SSID和SignalLevel
        QString ssid = wifiInfo.value("ssid");
        if(ssid==""){
            ssid = "<hiddenSSID>";
        }
        QString signalLevel = wifiInfo.value("signal level");
        
        // 删除旧的列表项(Qt会自行管理，也没有手动删除的函数）
        // 创建新的列表项并设置文本
        QTableWidgetItem *_item_ssid = new QTableWidgetItem(ssid);
        QTableWidgetItem *_item_signallevel = new QTableWidgetItem(signalLevel);
        
        // 设置样式
        _item_ssid->setTextAlignment(Qt::AlignCenter);
        _item_signallevel->setTextAlignment(Qt::AlignCenter);
        
        
        // 添加到列表中
        tablewidget->setItem(i,0,_item_ssid);
        tablewidget->setItem(i,1,_item_signallevel);
        
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
        // 正式开始连接wifi
        if(wfc->connectWIFI(ssid,password)){
            qDebug()<<"wifi connect success!";
            saveData("ssid", ssid);// 保存帐密
            saveData("password", password);
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
void WIFIPannel::initdefaultWIFI(){
    QString ssid = loadData("ssid", "Huanzze").toString();
    QString password = loadData("password", "whl369258147").toString();
    if(wfc->connectWIFI(ssid,password)){
        qDebug()<<"initdefaultWIFI success!";
    }else{
        qDebug()<<"initdefaultWIFI failed!";
    }
}
void WIFIPannel::saveData(const QString &key, const QVariant &value){
    QSettings settings; // 默认构造函数会使用应用程序的组织和域名作为设置的名称
    settings.setValue(key, value);
}
QVariant WIFIPannel::loadData(const QString &key, const QVariant &defaultValue)
{
    QSettings settings;
    return settings.value(key, defaultValue);
}
