#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //  窗口标题
    setWindowTitle("TCP - 服务器");

    // 默认端口号
    ui->port->setText("8899");

    // 创建监听的服务器对象
    m_server = new QTcpServer(this);

    // 当启动按钮被按下，服务器启动监听
    connect(ui->start, &QPushButton::clicked, this, [=] ()
    {
        unsigned short port = ui->port->text().toUShort();
        // 服务器监听接口
        m_server->listen(QHostAddress::Any, port);
        ui->start->setDisabled(true);
    });

    // 当有新的客户端连接
    connect(m_server, &QTcpServer::newConnection, this, [=] ()
    {
        // 服务器从连接队列中取出一个客户端建立连接，并返回与客户端通信的套接字
        m_tcp = m_server->nextPendingConnection();
        ui->record->append("成功和客户端建立了连接...");
        m_status->setPixmap(QPixmap(":/resources/connect.png").scaled(20, 20));

        // connect注册信号对应回调时，信号发送者必须是实例化对象
        // 因此下面两个connect操作，要写在m_tcp实例化之后

        // 当可以接收数据（有数据到达），调用readAll读取数据，并显示在消息记录文本框
        connect(m_tcp, &QTcpSocket::readyRead, this, [=]()
        {
            QByteArray data = m_tcp->readAll();
            ui->record->append("客户端：" + data);
        });

        // 断开连接
        connect(m_tcp, &QTcpSocket::disconnected, this, [=] ()
        {
            ui->record->append("客户端已经断开了连接...");
            m_tcp->close();
            // m_server对象释放后，m_tcp对象也会释放
            // 提前手动释放，节约套接字资源
            m_tcp->deleteLater(); // delete m_tcp
            m_status->setPixmap(QPixmap(":/resources/disconnect.png").scaled(20, 20));
        });
    });

    // 发送信息
    connect(ui->send, &QPushButton::clicked, this, [=] ()
    {
        // 将数据以纯文本方式取出，QString
        QString msg = ui->msg->toPlainText();
        // 需要转换成utf8才能发送
        m_tcp->write(msg.toUtf8());
        ui->record->append("服务器：" + msg);
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

