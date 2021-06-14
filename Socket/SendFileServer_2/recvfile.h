#ifndef RECVFILE_H
#define RECVFILE_H

#include <QThread>
#include <QTcpSocket>
#include <QRunnable>
#include <QFile>

class RecvFile : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit RecvFile(QTcpSocket* tcp, QFile* file, QObject *parent = nullptr);

    void run() override;

signals:
    void finish();

private:
    QTcpSocket* m_tcp;
    QFile* m_file;
};

#endif // RECVFILE_H
