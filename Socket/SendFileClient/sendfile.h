#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include <QTcpSocket>

class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QObject *parent = nullptr);

    // 连接服务器
    void connectServer(QString ip, unsigned short port);

    // 发送文件
    void sendFile(QString path);

signals:
    void connected();
    void disconnected();
    void curPercent(int num);

private:
    QTcpSocket* m_tcp;
};

#endif // SENDFILE_H
