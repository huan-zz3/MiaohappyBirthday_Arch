#ifndef WIFIWPA_PACKAGE_H
#define WIFIWPA_PACKAGE_H

#include <QObject>

class WIFIwpa_package : public QObject
{
    Q_OBJECT
public:
    explicit WIFIwpa_package(QObject *parent = nullptr);
    
signals:
    
};

#endif // WIFIWPA_PACKAGE_H
