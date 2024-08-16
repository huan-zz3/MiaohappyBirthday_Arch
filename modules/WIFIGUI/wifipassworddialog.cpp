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
    
    // 创建按钮
//    okButton = new QPushButton(tr("确认"), this);
//    cancelButton = new QPushButton(tr("取消"), this);
    
    // 连接信号槽
//    connect(okButton, &QPushButton::clicked, this, &WifiPasswordDialog::onOkButtonClicked);
//    connect(cancelButton, &QPushButton::clicked, this, &WifiPasswordDialog::onCancelButtonClicked);
    
    // 布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(passwordEdit);
//    layout->addWidget(okButton);
//    layout->addWidget(cancelButton);
//    setLayout(layout);
}

WifiPasswordDialog::~WifiPasswordDialog()
{
    delete ui;
}
QString WifiPasswordDialog::getPassword() const
{
    return passwordEdit->text();
}

//void WifiPasswordDialog::onOkButtonClicked()
//{
//    accept(); // 关闭对话框并设置结果码为Accepted
//}

//void WifiPasswordDialog::onCancelButtonClicked()
//{
//    reject(); // 关闭对话框并设置结果码为Rejected
//}
