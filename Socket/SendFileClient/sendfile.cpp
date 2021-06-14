#include "sendfile.h"

#include <QFile>
#include <QFileInfo>
#include <QHostAddress>
#include <QThread>
#include <QDebug>

SendFile::SendFile(QObject *parent) : QObject(parent)
{

}

void SendFile::connectServer(QString ip, unsigned short port)
{
    qDebug() << "连接服务器线程：" << QThread::currentThread();
    m_tcp = new QTcpSocket;
    m_tcp->connectToHost(QHostAddress(ip), port);

    // 通知主线程连接成功，这里可以使用信号转接
    // 这里转接原因是主线程无法获取m_tcp对象，无法注册
    // 主线程可以获取SendFile对象，可以进行转接
    connect(m_tcp, &QTcpSocket::connected, this, &SendFile::connected);
    connect(m_tcp, &QTcpSocket::disconnected, this, [=] ()
    {
        m_tcp->close();
        m_tcp->deleteLater();
        // 添加emit，表明是发送信号
        emit SendFile::disconnected();
    });
}

void SendFile::sendFile(QString path)
{
    qDebug() << "发送文件线程：" << QThread::currentThread();
    // 获取文件句柄
    QFile file(path);
    QFileInfo info(path);
    int fileSize = info.size();

    file.open(QFile::ReadOnly);

    // 逐行读文件
    while (!file.atEnd())
    {
        // 添加静态变量记录已发送长度
        static int num = 0;
        // 发送文件前先发送文件长度
        if (num == 0)
        {
            // 将int转换成char*，4字节
            m_tcp->write((char*)&fileSize, 4);
        }
        QByteArray line = file.readLine();
        num += line.size();
        int percent = (num * 100 / fileSize);
        emit curPercent(percent);
        m_tcp->write(line);
    }
}
