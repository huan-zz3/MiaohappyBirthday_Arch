#include "wifipassworddialog.h"
#include "ui_wifipassworddialog.h"

WifiPasswordDialog::WifiPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WifiPasswordDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("WiFi Password"));
    
    // 创建编辑框用于输入密码
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password); // 密码掩码显示
    
    // 布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(passwordEdit);
}

WifiPasswordDialog::~WifiPasswordDialog()
{
    delete ui;
}
QString WifiPasswordDialog::getPassword() const
{
    return passwordEdit->text();
}

