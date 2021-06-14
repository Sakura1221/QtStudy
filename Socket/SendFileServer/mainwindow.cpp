#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recvfile.h"

#include <QDebug>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "服务器主线程：" << QThread::currentThread();

     setWindowTitle("服务器");
    ui->port->setText("8989");

    /* 服务器初始化 */
    // 设置监听套接字
    m_server = new QTcpServer(this);
    // 按下按钮开始监听
    connect(ui->startServer, &QPushButton::clicked, m_server, [=] ()
    {
        unsigned short port = ui->port->text().toUShort();
        m_server->listen(QHostAddress::Any, port);
        ui->startServer->setDisabled(true);
    });
    // 监听到新连接
    connect(m_server, &QTcpServer::newConnection, this, [=] ()
    {
        QTcpSocket* tcp = m_server->nextPendingConnection();
        // 创建子线程的同时传递通信套接字
        RecvFile* recvThread = new RecvFile(tcp);

        connect(recvThread, &RecvFile::finish, this, [=] ()
        {
            recvThread->quit();
            recvThread->wait();
            recvThread->deleteLater();
            QMessageBox::information(this, "文件接收", "文件接收完毕!");
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

