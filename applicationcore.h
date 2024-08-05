#ifndef APPLICATIONCORE_H
#define APPLICATIONCORE_H

#include <QObject>

class ApplicationCore : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationCore(QObject *parent = nullptr);
    
signals:
    
};

#endif // APPLICATIONCORE_H
