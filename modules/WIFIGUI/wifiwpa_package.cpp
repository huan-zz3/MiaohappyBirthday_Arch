#include "wifiwpa_package.h"
#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
#include <thread>

WIFIwpa_package::WIFIwpa_package(QObject *parent) : IWIFIControl(parent)
{
    openControlInterface();
}
void WIFIwpa_package::openControlInterface(){
    ctrl = wpa_ctrl_open("/var/run/wpa_supplicant/wlan0");
    if (!ctrl) {
        qDebug()<<"Could not open control interface";
        isInterfaceOpened = false;
        return;
    }
    isInterfaceOpened = true;
}

QList<QMap<QString,QString>> WIFIwpa_package::getWIFIlist(){
    QList<QMap<QString, QString>> list;
    const char *cmd = "SCAN";
    char reply[1024] = {0};
    size_t reply_len;
    reply_len = sizeof(reply) - 1;
    
    int res = wpa_ctrl_request(ctrl, cmd, strlen(cmd), reply, &reply_len, nullptr);
    if (res != 0) {
        std::cout<<res<<std::endl;
        qDebug()<<"Failed to send SCAN command";
        return list;
    }
    
    QEventLoop loop;
    QTimer timer;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(3000);
    loop.exec();
    
    const char *cmd2 = "SCAN_RESULTS";
    char reply2[10240] = {0};
    size_t reply_len2;
    reply_len2 = sizeof(reply2) - 1;
    res = wpa_ctrl_request(ctrl, cmd2, strlen(cmd2), reply2, &reply_len2, nullptr);
    if (res != 0) {
        std::cout<<res<<std::endl;
        qDebug()<<"Failed to send SCAN_RESULTS command";
        return list;
    }
    
    std::cout << "Received status:\n"<< reply2 <<std::endl;
    QString qreply(reply2);
//    qDebug()<<qreply;
    
    QStringList lines = qreply.split('\n');
    
    for (const QString& line : lines) {
        // 跳过空行
        if (line.trimmed().isEmpty()) {
            continue;
        }
        // 分割每一行
        QStringList fields = line.split('\t');
        if (fields.size() >= 4) {  // 确保有足够的字段
            QString ssid = fields[4];
            QString signalLevel = fields[2];
            
//            replaceHexChar(&ssid);
            
            // 创建映射并将数据添加进去
            QMap<QString, QString> entry;
            entry.insert("ssid", ssid);
            entry.insert("signal level", signalLevel);
            
            // 添加映射到列表
            list.append(entry);
        }
    }
    
    // 打印结果验证
    for (const auto& entry : list) {
        qDebug() << "ssid:" << entry["ssid"] << "Signal Level:" << entry["signal level"];
    }
    return list;
}
bool WIFIwpa_package::isConnected(){
    char buf[1024];
    size_t buflen = sizeof(buf);
    
    // Send the STATUS command to get the current status
    if (wpa_ctrl_request(ctrl, "STATUS", strlen("STATUS"), buf, &buflen, NULL) < 0) {
        std::cerr << "Failed to request status." << std::endl;
        return false;
    }
    
    // Check for the presence of "wpa_state=COMPLETED" or "bssid="
    const char* state_completed = "wpa_state=COMPLETED";
    const char* bssid_prefix = "bssid=";
    if (strstr(buf, state_completed) != NULL || strstr(buf, bssid_prefix) != NULL) {
        return true;
    }
    
    return false;
}
bool WIFIwpa_package::connectWIFI(QString _name, QString _password){
    const char *ssid = _name.toStdString().c_str();
    const char *password = _password.toStdString().c_str();
    
    qDebug()<<"ssid:"<<ssid;
    qDebug()<<"password:"<<password;
    
//    const char *pu8SSID = "Huanzze";
//    const char *pu8Secret = "whl369258147";
    // char *pu8EncryptType

    char au8ReplyBuf[2048] = {"\0"};  // 初始化缓冲区，用于接收回复消息
    size_t reply_len;                 // 回复消息长度
    int ret;                          // 返回值
    int s32NetId = -1;                // 网络ID
//    char au8Path[128] = {"\0"};       // 控制套接字路径

//    struct wpa_ctrl *ctrl; 
//    // 打开wpa_supplicant的控制套接字
//    sprintf(au8Path, "/var/run/wpa_supplicant/wlan0");  // 构造路径字符串
//    ctrl = wpa_ctrl_open(au8Path);  // 打开控制接口
//    if (ctrl == NULL) {  // 如果打开失败
//        printf("\x1b[31m""%s %d, wpa_ctrl_open failed:%s!\n""\x1b[0m", __FILE__, __LINE__, strerror(errno));  // 输出错误信息
//        return false;  // 返回错误码
//    }

    // 发送添加新网络的命令
    memset(au8ReplyBuf, '\0', sizeof(au8ReplyBuf));  // 清空回复缓冲区
    reply_len = sizeof(au8ReplyBuf) - 1;             // 设置回复缓冲区最大长度
    ret = wpa_ctrl_request(ctrl, "ADD_NETWORK", strlen("ADD_NETWORK"), au8ReplyBuf, &reply_len, NULL);  // 发送请求
    if (ret == 0) {  // 如果请求成功
        au8ReplyBuf[reply_len] = '\0';  // 确保字符串以'\0'结尾
    }

    s32NetId = atoi(au8ReplyBuf);  // 解析回复中的网络ID

    // 设置SSID
    char au8SsidBuf[128] = {"\0"};  // SSID设置命令缓冲区
    snprintf(au8SsidBuf, sizeof(au8SsidBuf) - 1, "SET_NETWORK %d ssid \"%s\"", s32NetId, ssid);  // 构造SSID设置命令
    memset(au8ReplyBuf, '\0', sizeof(au8ReplyBuf));  // 清空回复缓冲区
    reply_len = sizeof(au8ReplyBuf) - 1;             // 设置回复缓冲区最大长度
    ret = wpa_ctrl_request(ctrl, au8SsidBuf, strlen(au8SsidBuf), au8ReplyBuf, &reply_len, NULL);  // 发送请求
    if (ret == 0) {  // 如果请求成功
        au8ReplyBuf[reply_len] = '\0';  // 确保字符串以'\0'结尾
        printf("\x1b[32m""%s %d, reply_len:%d, au8ReplyBuf:%s\n""\x1b[0m", __FILE__, __LINE__, reply_len, au8ReplyBuf);  // 输出成功信息
    } else {  // 如果请求失败
        return false;  // 返回错误码
    }

    // 设置密码
    char au8PskBuf[128] = {"\0"};  // 密码设置命令缓冲区
    snprintf(au8PskBuf, sizeof(au8PskBuf) - 1, "SET_NETWORK %d psk \"%s\"", s32NetId, password);  // 构造密码设置命令
    memset(au8ReplyBuf, '\0', sizeof(au8ReplyBuf));  // 清空回复缓冲区
    reply_len = sizeof(au8ReplyBuf) - 1;             // 设置回复缓冲区最大长度
    ret = wpa_ctrl_request(ctrl, au8PskBuf, strlen(au8PskBuf), au8ReplyBuf, &reply_len, NULL);  // 发送请求
    if (ret == 0) {  // 如果请求成功
        au8ReplyBuf[reply_len] = '\0';  // 确保字符串以'\0'结尾
        printf("\x1b[32m""%s %d, reply_len:%d, au8ReplyBuf:%s\n""\x1b[0m", __FILE__, __LINE__, reply_len, au8ReplyBuf);  // 输出成功信息
    } else {  // 如果请求失败
        return false;  // 返回错误码
    }

    // 启用网络
    char au8EnableBuf[64] = {"\0"};  // 启用网络命令缓冲区
    snprintf(au8EnableBuf, sizeof(au8EnableBuf) - 1, "ENABLE_NETWORK %d", s32NetId);  // 构造启用网络命令
    memset(au8ReplyBuf, '\0', sizeof(au8ReplyBuf));  // 清空回复缓冲区
    reply_len = sizeof(au8ReplyBuf) - 1;             // 设置回复缓冲区最大长度
    ret = wpa_ctrl_request(ctrl, au8EnableBuf, strlen(au8EnableBuf), au8ReplyBuf, &reply_len, NULL);  // 发送请求
    if (ret == 0) {  // 如果请求成功
        au8ReplyBuf[reply_len] = '\0';  // 确保字符串以'\0'结尾
        printf("\x1b[32m""%s %d, reply_len:%d, au8ReplyBuf:%s\n""\x1b[0m", __FILE__, __LINE__, reply_len, au8ReplyBuf);  // 输出成功信息
    } else {  // 如果请求失败
        return false;  // 返回错误码
    }
    
    // 保存网络
    char au8SaveBuf[64] = {"\0"};  // 保存网络命令缓冲区
    snprintf(au8SaveBuf, sizeof(au8SaveBuf) - 1, "SAVE_CONFIG");  // 构造保存网络命令
    memset(au8ReplyBuf, '\0', sizeof(au8ReplyBuf));  // 清空回复缓冲区
    reply_len = sizeof(au8ReplyBuf) - 1;             // 设置回复缓冲区最大长度
    ret = wpa_ctrl_request(ctrl, au8SaveBuf, strlen(au8SaveBuf), au8ReplyBuf, &reply_len, NULL);  // 发送请求
    if (ret == 0) {  // 如果请求成功
        au8ReplyBuf[reply_len] = '\0';  // 确保字符串以'\0'结尾
        printf("\x1b[32m""%s %d, reply_len:%d, au8SaveBuf:%s\n""\x1b[0m", __FILE__, __LINE__, reply_len, au8ReplyBuf);  // 输出成功信息
    } else {  // 如果请求失败
        return false;  // 返回错误码
    }
    
    
    if(!runDhclient()){
        qDebug()<<"runDhclient ERR!";
        return false;
    }

    return true;  // 返回最终结果
}
bool WIFIwpa_package::runDhclient(){
    QProcess dhclientProcess;
    
    connect(&dhclientProcess, &QProcess::readyReadStandardOutput,this, [&dhclientProcess](){
        QByteArray data = dhclientProcess.readAllStandardOutput();
        qDebug() << "dhclient standard output:" << data;
    });
    connect(&dhclientProcess, &QProcess::readyReadStandardError,this, [&dhclientProcess](){
        QByteArray data = dhclientProcess.readAllStandardError();
        qDebug() << "dhclient standard error:" << data;
    });
    
//    dhclientProcess.start(QString("echo %1 | sudo -S dhclient wlan0").arg(password));
    dhclientProcess.start("sudo dhclient wlan0");
//    dhclientProcess.start(":/shell/src/shell/run_dhclient.sh", QStringList() << password);
//    system("echo orangepi | sudo -S dhclient wlan0");
    
    if (!dhclientProcess.waitForStarted()) {
        qDebug() << "Failed to start dhclient process.";
        return false;
    }
    
    if (!dhclientProcess.waitForFinished()) {
        qDebug() << "dhclient process failed to finish.";
        return false;
    }
    
    if (dhclientProcess.exitCode() != 0) {
        qDebug() << "dhclient process failed with exit code:" << dhclientProcess.exitCode();
        return false;
    }
    return true;
}

bool WIFIwpa_package::disconnectWIFI(){
    char au8ReplyBuf[2048] = {"\0"};  // 初始化缓冲区，用于接收回复消息
    size_t reply_len;                 // 回复消息长度
    int ret;                          // 返回值
    char disconnectBuf[128] = {"\0"};  // DISCONNECT设置命令缓冲区
    
    snprintf(disconnectBuf, sizeof(disconnectBuf) - 1, "DISCONNECT");  // 构造DISCONNECT设置命令
    memset(au8ReplyBuf, '\0', sizeof(au8ReplyBuf));  // 清空回复缓冲区
    reply_len = sizeof(au8ReplyBuf) - 1;             // 设置回复缓冲区最大长度
    ret = wpa_ctrl_request(ctrl, disconnectBuf, strlen(disconnectBuf), au8ReplyBuf, &reply_len, NULL);  // 发送请求
    if (ret == 0) {  // 如果请求成功
        au8ReplyBuf[reply_len] = '\0';  // 确保字符串以'\0'结尾
        printf("\x1b[32m""%s %d, reply_len:%d, au8ReplyBuf:%s\n""\x1b[0m", __FILE__, __LINE__, reply_len, au8ReplyBuf);  // 输出成功信息
    } else {  // 如果请求失败
        return false;  // 返回错误码
    }
    return true;
}
void WIFIwpa_package::replaceHexChar(QString *_string){
    if (_string->startsWith("\\") && _string->contains("\\x")) {
        // 替换掉所有转义序列
        *_string = _string->replace("\\x", "").replace("\\", "");
        // 分割得到十六进制值
        QStringList hexValues = _string->split("\\");
        QByteArray ssidBytes;
        for (const QString& hexValue : hexValues) {
            if (!hexValue.isEmpty()) {
                // 将十六进制转换为字节
                ssidBytes.append(hexValue.toLatin1(), 1);
            }
        }
        // 将字节转换为字符串
        *_string = QString::fromUtf8(ssidBytes);
    }
}


