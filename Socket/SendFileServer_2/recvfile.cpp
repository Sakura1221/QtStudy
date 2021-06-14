#include "recvfile.h"
#include <QDebug>

// 在子线程进行通信需要传入通信套接字
// 可以用信号槽，也可以在生成实例时直接传递
// 但都需要用成员变量存下来
RecvFile::RecvFile(QTcpSocket* tcp, QFile* file, QObject *parent) : QObject(parent), QRunnable()
{
    m_tcp = tcp;
    m_file = file;
}

void RecvFile::run()
{
    qDebug() << "服务器子线程：" << QThread::currentThread();

    static int count = 0;
    static int total = 0;
    if (count == 0)
    {
        m_tcp->read((char*)&total, 4);
    }
    QByteArray all = m_tcp->readAll();
    count += all.size();
    m_file->write(all);

    if (count == total)
    {
        m_tcp->close();
        m_file->close();
        emit finish();
    }
}
