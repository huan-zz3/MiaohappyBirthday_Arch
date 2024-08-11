#ifndef GRAPVIEW_CENTRE_H
#define GRAPVIEW_CENTRE_H

#include <QGraphicsView>
#include <QDebug>


class GrapView_centre : public QGraphicsView
{
public:
    explicit GrapView_centre(QGraphicsScene *, QWidget *parent = nullptr);
    void setBackground();
};

#endif // GRAPVIEW_CENTRE_H
