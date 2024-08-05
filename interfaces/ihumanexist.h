#ifndef IHUMANEXIST_H
#define IHUMANEXIST_H

#include <QObject>

class IHumanExist : public QObject
{
    Q_OBJECT
public:
    explicit IHumanExist(QObject *parent = nullptr):QObject(parent){};
    
signals:
    void signal_HumanExist();
    void signal_HumanNotExist();
};

#endif // IHUMANEXIST_H
