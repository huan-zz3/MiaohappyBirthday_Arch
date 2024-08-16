#ifndef GRAPVIEW_CENTRE_H
#define GRAPVIEW_CENTRE_H

#include <QDebug>
#include <QGraphicsView>
#include <QDebug>
#include <QMouseEvent>


class GrapView_centre : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GrapView_centre(QGraphicsScene *, QWidget *parent = nullptr);
    void setBackground();
    
private:
    void mousePressEvent(QMouseEvent *) override;
    
signals:
    void signal_MousePress(QGraphicsItem *);
};

#endif // GRAPVIEW_CENTRE_H
