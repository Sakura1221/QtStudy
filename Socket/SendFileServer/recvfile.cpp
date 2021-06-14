#include "recvfile.h"
#include <QFile>
#include <QDebug>

// 在子线程进行通信需要传入通信套接字
// 可以用信号槽，也可以在生成实例时直接传递
// 但都需要用成员变量存下来
RecvFile::RecvFile(QTcpSocket* tcp, QObject *parent) : QThread(parent)
{
    m_tcp = tcp;
}

void RecvFile::run()
{
    qDebug() << "服务器子线程：" << QThread::currentThread();

    // 新建文件对象
    QFile* file = new QFile("recv.txt");
    file->open(QFile::WriteOnly);

    // 接收数据
    connect(m_tcp, &QTcpSocket::readyRead, this, [=] ()
    {
        static int count = 0;
        static int total = 0;
        if (count == 0)
        {
            // 将int指针变成char指针
            m_tcp->read((char*)&total, 4);
        }
        // 读出剩余数据
        QByteArray all = m_tcp->readAll();
        count += all.size();
        file->write(all);

        // 数据接收完毕，关闭连接，关闭文件
        if (count == total)
        {
            m_tcp->close();
            m_tcp->deleteLater();
            file->close();
            file->deleteLater();
            emit finish();
        }
    });

    // 为了避免线程函数提前退出后，无法进行通信
    // 需要阻塞线程，持续监听套接字读事件
    exec();
}
