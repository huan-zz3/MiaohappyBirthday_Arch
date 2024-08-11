#include "ui_home.h"
#include "ui_ui_home.h"

UI_Home::UI_Home(QWidget *parent) :
    IHomeGUI(parent),
    ui(new Ui::UI_Home)
{
    ui->setupUi(this);
    initView();
    initsubScene();
    this->setCursor(Qt::BlankCursor);
//    showFullScreen();
}

UI_Home::~UI_Home()
{
    delete ui;
}
void UI_Home::initView(){
    qDebug()<<"here";
    
    mainScene = new QGraphicsScene(QRect(0,0,1024,600), this);
    mainView = new GrapView_home(mainScene ,this);
    mainView->resize(1024, 600);
    mainView->setFrameShape(QFrame::NoFrame);
    QPixmap bgPixmap(":/src/src/png/menuBackground-modified.png");
    QBrush backgroundBrush(bgPixmap);
    mainView->setBackgroundBrush(backgroundBrush);// 设置背景图
    
    subScene = new QGraphicsScene(QRect(0,0,666,306), this);
    QColor transparentColor(255,255,255,180);
    QBrush transparentBrush(transparentColor);
    subScene->setBackgroundBrush(transparentBrush);
    
    subView = new GrapView_centre(subScene);
    subView->resize(666, 306);
    subView->setFrameShape(QFrame::NoFrame);
    
    
    
    proxyWidget = mainScene->addWidget(subView);
    proxyWidget->setPos(185, 146);
    
}
void UI_Home::initsubScene(){
    // mask
    maskrect = new QGraphicsRectItem(0,0,360,220);
    QRadialGradient radialGradient(180,110,150,180,110);
    radialGradient.setColorAt(0, Qt::black);
    radialGradient.setColorAt(1, Qt::transparent);
    QBrush brush(radialGradient);
    maskrect->setBrush(brush);
    maskrect->setPen(QPen(Qt::NoPen));
    maskrect->setOpacity(0.7);
    maskrect->setPos(0, 0);
    subScene->addItem(maskrect);
    

    // time text
    time = new QGraphicsTextItem();
    time->setDefaultTextColor(Qt::white);
    time->setPos(30, 45);
    time->setFont(QFont(loadFont(":/font/src/font/321impact.ttf"), 50));
    timeString = "14:55:26";
    time->setPlainText(timeString);
    subScene->addItem(time);
    // date text
    date = new QGraphicsTextItem();
    date->setDefaultTextColor(Qt::white);
    date->setPos(60, 100);
    date->setFont(QFont(loadFont(":/font/src/font/Bock-Medium.ttf"), 30));
    dateString = "7/19/2024 Sat";
    date->setPlainText(dateString);
    subScene->addItem(date);
    // location text
    location = new QGraphicsTextItem();
    location->setDefaultTextColor(Qt::white);
    location->setPos(65, 160);
    location->setFont(QFont(loadFont(":/font/src/font/Crystal-Regular.ttf"), 20));
    locationString = "KaiFeng Henan";
    location->setPlainText(locationString);
    subScene->addItem(location);
    // menu picture
    pixmenu = new QGraphicsPixmapItem();
    pixmenu->setPixmap(QPixmap(":/src/src/png/menu.png"));
    pixmenu->setPos(10,260);
    pixmenu->setScale(0.2);
    subScene->addItem(pixmenu);
    
    // bless png
    bless = new QGraphicsPixmapItem();
    bless->setPixmap(QPixmap(":/src/src/png/bless.png"));
    bless->setPos(50,230);
    bless->setScale(1);
    subScene->addItem(bless);
    
    // temperaturenow text
    temperaturenow = new QGraphicsTextItem();
    temperaturenow->setDefaultTextColor(Qt::black);
    temperaturenow->setPos(420, 0);
    temperaturenow->setFont(QFont(loadFont(":/font/src/font/Rainbow-Party.ttf"), 50));
    temperaturenowString = "20℃";
    temperaturenow->setPlainText(temperaturenowString);
    subScene->addItem(temperaturenow);
    
    //weather icon
    weathericon[0]= new QGraphicsSvgItem();
    weathericonrenderer[0] = new QSvgRenderer(QString(":/weathericons/src/weathericons/100.svg"));
    weathericon[0]->setSharedRenderer(weathericonrenderer[0]);
    weathericon[0]->setScale(5);
    weathericon[0]->setPos(350,80);
    subScene->addItem(weathericon[0]);
    
    weathericon[1]= new QGraphicsSvgItem();
    weathericonrenderer[1] = new QSvgRenderer(QString(":/weathericons/src/weathericons/102.svg"));
    weathericon[1]->setSharedRenderer(weathericonrenderer[1]);
    weathericon[1]->setScale(5);
    weathericon[1]->setPos(450,80);
    subScene->addItem(weathericon[1]);
    
    weathericon[2]= new QGraphicsSvgItem();
    weathericonrenderer[2] = new QSvgRenderer(QString(":/weathericons/src/weathericons/104.svg"));
    weathericon[2]->setSharedRenderer(weathericonrenderer[2]);
    weathericon[2]->setScale(5);
    weathericon[2]->setPos(550,80);
    subScene->addItem(weathericon[2]);
    
    // week text
    QString weekFont = loadFont(":/font/src/font/SwimingFrog-Regular.ttf");
    week[0] = new QGraphicsTextItem();
    week[0]->setDefaultTextColor(Qt::black);
    week[0]->setPos(365+weektextXoffset, 160);
    week[0]->setFont(QFont(weekFont, 50));
    weekString[0] = "Sat";
    week[0]->setPlainText(weekString[0]);
    subScene->addItem(week[0]);
    
    week[1] = new QGraphicsTextItem();
    week[1]->setDefaultTextColor(Qt::black);
    week[1]->setPos(460+weektextXoffset, 160);
    week[1]->setFont(QFont(weekFont, 50));
    weekString[1] = "Sun";
    week[1]->setPlainText(weekString[1]);
    subScene->addItem(week[1]);
    
    week[2] = new QGraphicsTextItem();
    week[2]->setDefaultTextColor(Qt::black);
    week[2]->setPos(555+weektextXoffset, 160);
    week[2]->setFont(QFont(weekFont, 50));
    weekString[2] = "Mon";
    week[2]->setPlainText(weekString[2]);
    subScene->addItem(week[2]);
    
    // temperaturescale text
    QString tempFont = loadFont(":/font/src/font/HFSantaMonica.ttf");
    temperaturescale[0][0] = new QGraphicsTextItem();
    temperaturescale[0][0]->setDefaultTextColor(Qt::black);
    temperaturescale[0][0]->setPos(350+temptextXoffset, 220);
    temperaturescale[0][0]->setFont(QFont(tempFont, 25));
    temperaturescaleString[0][0] = "19℃";
    temperaturescale[0][0]->setPlainText(temperaturescaleString[0][0]);
    subScene->addItem(temperaturescale[0][0]);
    
    temperaturescale[1][0] = new QGraphicsTextItem();
    temperaturescale[1][0]->setDefaultTextColor(Qt::black);
    temperaturescale[1][0]->setPos(450+temptextXoffset, 220);
    temperaturescale[1][0]->setFont(QFont(tempFont, 25));
    temperaturescaleString[1][0] = "17℃";
    temperaturescale[1][0]->setPlainText(temperaturescaleString[1][0]);
    subScene->addItem(temperaturescale[1][0]);
    
    temperaturescale[2][0] = new QGraphicsTextItem();
    temperaturescale[2][0]->setDefaultTextColor(Qt::black);
    temperaturescale[2][0]->setPos(550+temptextXoffset, 220);
    temperaturescale[2][0]->setFont(QFont(tempFont, 25));
    temperaturescaleString[2][0] = "15℃";
    temperaturescale[2][0]->setPlainText(temperaturescaleString[2][0]);
    subScene->addItem(temperaturescale[2][0]);
    
    temperaturescale[0][1] = new QGraphicsTextItem();
    temperaturescale[0][1]->setDefaultTextColor(Qt::black);
    temperaturescale[0][1]->setPos(350+temptextXoffset, 250);
    temperaturescale[0][1]->setFont(QFont(tempFont, 25));
    temperaturescaleString[0][1] = "22℃";
    temperaturescale[0][1]->setPlainText(temperaturescaleString[0][1]);
    subScene->addItem(temperaturescale[0][1]);
    
    temperaturescale[1][1] = new QGraphicsTextItem();
    temperaturescale[1][1]->setDefaultTextColor(Qt::black);
    temperaturescale[1][1]->setPos(450+temptextXoffset, 250);
    temperaturescale[1][1]->setFont(QFont(tempFont, 25));
    temperaturescaleString[1][1] = "20℃";
    temperaturescale[1][1]->setPlainText(temperaturescaleString[1][1]);
    subScene->addItem(temperaturescale[1][1]);
    
    temperaturescale[2][1] = new QGraphicsTextItem();
    temperaturescale[2][1]->setDefaultTextColor(Qt::black);
    temperaturescale[2][1]->setPos(550+temptextXoffset, 250);
    temperaturescale[2][1]->setFont(QFont(tempFont, 25));
    temperaturescaleString[2][1] = "18℃";
    temperaturescale[2][1]->setPlainText(temperaturescaleString[2][1]);
    subScene->addItem(temperaturescale[2][1]);
}
QString UI_Home::loadFont(QString fontpath){
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

void UI_Home::showHomeForm()  {
    this->showFullScreen();
}
void UI_Home::closeHomeForm()  {
    this->hide();
}
void UI_Home::setNowTemp(QString _temp)  {
    temperaturenowString = _temp;
    temperaturenow->setPlainText(temperaturenowString);
}
void UI_Home::setTodayMaxTemp(QString _temp)  {
    temperaturescaleString[0][0] = _temp;
    temperaturescale[0][0]->setPlainText(temperaturescaleString[0][0]);
}
void UI_Home::setTodayMinTemp(QString _temp)  {
    temperaturescaleString[0][1] = _temp;
    temperaturescale[0][1]->setPlainText(temperaturescaleString[0][1]);
}
void UI_Home::setTomorrowMaxTemp(QString _temp)  {
    temperaturescaleString[1][0] = _temp;
    temperaturescale[1][0]->setPlainText(temperaturescaleString[1][0]);
}
void UI_Home::setTomorrowMinTemp(QString _temp)  {
    temperaturescaleString[1][1] = _temp;
    temperaturescale[1][1]->setPlainText(temperaturescaleString[1][1]);
}
void UI_Home::setThirdayMaxTemp(QString _temp)  {
    temperaturescaleString[2][0] = _temp;
    temperaturescale[2][0]->setPlainText(temperaturescaleString[2][0]);
}
void UI_Home::setThirdayMinTemp(QString _temp)  {
    temperaturescaleString[2][1] = _temp;
    temperaturescale[2][1]->setPlainText(temperaturescaleString[2][1]);
}
void UI_Home::setTodayIcon(QString _path)  {
    QResource resource(_path);
    if (resource.isValid()) {
        QSvgRenderer *_lastrenderer = weathericon[0]->renderer();
        QSvgRenderer *_nextrenderer = new QSvgRenderer(_path);
        weathericon[0]->setSharedRenderer(_nextrenderer);
        _lastrenderer->deleteLater();
    }else{
        qDebug()<<"Icon path erro";
    }
}
void UI_Home::setTomorrowIcon(QString _path)  {
    QResource resource(_path);
    if (resource.isValid()) {
        QSvgRenderer *_lastrenderer = weathericon[1]->renderer();
        QSvgRenderer *_nextrenderer = new QSvgRenderer(_path);
        weathericon[1]->setSharedRenderer(_nextrenderer);
        _lastrenderer->deleteLater();
    }else{
        qDebug()<<"Icon path erro";
    }
}
void UI_Home::setThirdayIcon(QString _path)  {
    QResource resource(_path);
    if (resource.isValid()) {
        QSvgRenderer *_lastrenderer = weathericon[2]->renderer();
        QSvgRenderer *_nextrenderer = new QSvgRenderer(_path);
        weathericon[2]->setSharedRenderer(_nextrenderer);
        _lastrenderer->deleteLater();
    }else{
        qDebug()<<"Icon path erro";
    }
}
void UI_Home::setNowTime(QString _time)  {
    timeString = _time;
    time->setPlainText(timeString);
}
void UI_Home::setTodayDate(QString _date)  {
    dateString = _date;
    date->setPlainText(dateString);
}
void UI_Home::setNowLocation(QString _location)  {
    locationString = _location;
    location->setPlainText(locationString);
}
void UI_Home::setTodayWeek(QString _week)  {
    weekString[0] = _week;
    week[0]->setPlainText(weekString[0]);
}
void UI_Home::setTomorrowWeek(QString _week){
    weekString[1] = _week;
    week[1]->setPlainText(weekString[1]);
}
void UI_Home::setThirdayWeek(QString _week){
    weekString[2] = _week;
    week[2]->setPlainText(weekString[2]);
}
