#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostAddress>
#include <QTcpSocket>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //  窗口标题
    setWindowTitle("TCP - 客户端");

    // 默认ip和端口号
    ui->port->setText("8899");
    ui->ip->setText("127.0.0.1");

    // 创建用来通信的客户端套接字
    m_tcp = new QTcpSocket(this);

    // 当服务器有消息发过来
    connect(m_tcp, &QTcpSocket::readyRead, this, [=] ()
    {
        QByteArray data = m_tcp->readAll();
        ui->record->append("服务器：" + data);
    });

    // 当按钮显示连接时被按下，与服务器建立连接
    // 注意只是建立连接，不一定成功，需要m_tcp返回connected信号
    // 当按钮显示断开时被按下，与服务器断开连接，同样也不一定成功，需要m_tcp返回disconnected信号
    connect(ui->connect, &QPushButton::clicked, this, [=] ()
    {
        if (ui->connect->text() == "连接")
        {
            QString ip = ui->ip->text();
            unsigned short port = ui->port->text().toUShort();
            // 客户端连接服务器接口
            // 通过QHostAddress封装ip地址
            m_tcp->connectToHost(QHostAddress(ip), port);
        }
        else
        {
            m_tcp->close();
        }
    });

    // 客户端连接成功
    connect(m_tcp, &QTcpSocket::connected, this, [=] ()
    {
        // 连接成功后状态栏变成已连接，按钮变成断开连接
        m_status->setPixmap(QPixmap(":/resources/connect.png").scaled(20, 20));
        ui->connect->setText("断开");
        ui->record->append("客户端成功连接到了服务器...");
    });

    // 发送信息
    connect(ui->send, &QPushButton::clicked, this, [=] ()
    {
        // 将数据以纯文本方式取出，QString
        QString msg = ui->msg->toPlainText();
        // 需要转换成utf8才能发送
        m_tcp->write(msg.toUtf8());
        ui->record->append("客户端：" + msg);
    });

    // 断开连接
    connect(m_tcp, &QTcpSocket::disconnected, this, [=] ()
    {
        m_tcp->close();
        // 父对象释放后，m_tcp对象也会释放
        // 提前手动释放，节约套接字资源
        m_tcp->deleteLater(); // delete m_tcp
        m_status->setPixmap(QPixmap(":/resources/disconnect.png").scaled(20, 20));
        ui->connect->setText("连接");
        ui->record->append("已经与服务器断开连接...");
    });

    // 状态栏
    m_status = new QLabel; // 会被设置在状态栏内，不需要指定父对象
    m_status->setPixmap(QPixmap(":/resources/disconnect.png").scaled(20, 20));
    ui->statusbar->addWidget(new QLabel("连接状态：")); // 标签栏不需要修改，传入临时对象即可
    ui->statusbar->addWidget(m_status);
}

MainWindow::~MainWindow()
{
    delete ui;
}
