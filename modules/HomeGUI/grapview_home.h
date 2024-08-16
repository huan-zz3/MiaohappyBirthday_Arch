#ifndef GRAPVIEW_HOME_H
#define GRAPVIEW_HOME_H

#include <QObject>
#include <QGraphicsView>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>


#define SLIDE_DISTANCE 20
#define SLIDE_WAITIME 500

class GrapView_home : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GrapView_home(QGraphicsScene *, QWidget *parent = nullptr);
    
private:
    QPoint lastMousePos;
    QTimer *timer;
    bool slideValid;
    
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    
signals:
    void signal_slideToTop();
    void signal_slideToBottom();
};

#endif // GRAPVIEW_HOME_H
