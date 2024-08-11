#ifndef WIFIPANNEL_H
#define WIFIPANNEL_H

#include <QObject>

class WIFIPannel : public QObject
{
    Q_OBJECT
public:
    explicit WIFIPannel(QObject *parent = nullptr);
    
signals:
    
};

#endif // WIFIPANNEL_H
