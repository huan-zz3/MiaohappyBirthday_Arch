#include "grapview_centre.h"

GrapView_centre::GrapView_centre(QGraphicsScene *scene,  QWidget *parent)
    : QGraphicsView(scene, parent)
{
    setBackground();
    this->setCursor(Qt::BlankCursor);
//    resize(354, 242);
}
void GrapView_centre::setBackground(){
    setAttribute(Qt::WA_TranslucentBackground, true);
    // 创建QPalette对象并设置背景色为白色
    QPalette myPalette = palette();
    myPalette.setColor(QPalette::Base, Qt::transparent); // 设置背景色为白色
    
    // 注意：不透明度设置通常是对整个窗口或视图而言，而不是单独设置背景颜色的不透明度。
    // 但我们可以模拟70%的不透明效果，例如，通过在一个具有半透明效果的场景上绘制白色矩形。
    // 如果需要整个视图（包括其内容）有70%的不透明度，可以使用：
//    setWindowOpacity(0.5);
    
    // 应用修改后的调色板
    setPalette(myPalette);
    
    // 为了使背景完全不透明并显示为白色（同时保持视图内容可能的透明效果），确保场景本身没有设置透明度，
    // 或者如果你想要场景中的内容也有透明效果，则调整场景中的项来匹配所需的不透明度。
}
