#ifndef WIFIPASSWORDDIALOG_H
#define WIFIPASSWORDDIALOG_H

#include <QDialog>
//#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

namespace Ui {
class WifiPasswordDialog;
}

class WifiPasswordDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit WifiPasswordDialog(QWidget *parent = nullptr);
    ~WifiPasswordDialog();
    
    QString getPassword() const;
    
private slots:
//    void onOkButtonClicked();
//    void onCancelButtonClicked();
    
private:
    Ui::WifiPasswordDialog *ui;
    QLineEdit *passwordEdit;
//    QPushButton *okButton;
//    QPushButton *cancelButton;
};

#endif // WIFIPASSWORDDIALOG_H
