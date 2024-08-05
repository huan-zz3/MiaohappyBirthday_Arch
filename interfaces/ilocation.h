#ifndef ILOCATION_H
#define ILOCATION_H

#include <QObject>
#include <QString>

class ILocation : public QObject
{
    Q_OBJECT
public:
    explicit ILocation(QObject *parent = nullptr):QObject(parent){};
    virtual QString getNowLocation() = 0;
    
signals:
    
};

#endif // ILOCATION_H
