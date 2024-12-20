#include "ui_wallpaper.h"
#include "ui_ui_wallpaper.h"

UI_Wallpaper::UI_Wallpaper(QWidget *parent) :
    IWallpaper(parent),
    ui(new Ui::UI_Wallpaper)
{
    ui->setupUi(this);
    this->resize(1024,600);
    setCursor(Qt::BlankCursor);
    searchforWallpaper();
    
    this->nextPicture();
    
    switchtimer = new QTimer();
    connect(switchtimer, &QTimer::timeout, this, &UI_Wallpaper::nextPicture);
    switchtimer->start(5000);
}

UI_Wallpaper::~UI_Wallpaper()
{
    delete ui;
}

void UI_Wallpaper::showWallpaperForm(){
    this->showFullScreen();
    this->raise();
    this->activateWindow();
}
void UI_Wallpaper::closeWallpaperForm(){
    hide();
}
void UI_Wallpaper::nextPicture(){
    QString nextPath;
    currentImage++;
    if(currentImage >=filePaths.count()){
        currentImage = 0;
    }
    nextPath = filePaths.at(currentImage);
    applyNewWallpaper(nextPath);
}
void UI_Wallpaper::lastPicture(){
    QString nextPath;
    currentImage--;
    if(currentImage < 0){
        currentImage = filePaths.count()-1;
    }
    nextPath = filePaths.at(currentImage);
    applyNewWallpaper(nextPath);
}
void UI_Wallpaper::setIntervalTime(int msec){
    switchtimer->setInterval(msec);
}
void UI_Wallpaper::searchforWallpaper(){
    QDir directory(DIRECTORYPATH);
//    qDebug()<<QDir::currentPath() + DIRECTORYPATH;
    
//    QStringList filters;
//    filters << "*.png" << "*.jpg"; // 添加更多格式只需追加，如 "*.gif", "*.bmp"
    QFileInfoList fileInfoList = directory.entryInfoList(QDir::Files | QDir::NoDotAndDotDot); // 列出所有文件，不包括"."和".." 
    
    for (const QFileInfo &fileInfo : fileInfoList)
    {
        filePaths.append(fileInfo.filePath());
    }
    
    // 现在，filePaths 列表包含了指定目录下所有文件的完整路径
    foreach (const QString &filePath, filePaths)
    {
        qDebug() << filePath;
    }
}
void UI_Wallpaper::applyNewWallpaper(QString &nextPath){
    QPixmap pixmap(nextPath);
    // 缩放图片以适应窗口大小（可选）
    // 注意：此步骤可能会扭曲图片，根据需要调整缩放模式
    pixmap = pixmap.scaled(this->size(),  Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);
}
