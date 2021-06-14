#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QThread>
#include <QFileDialog>
#include <QDebug>
#include "sendfile.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "客户端主线程：" << QThread::currentThread();

    setWindowTitle("客户端");
    ui->ip->setText("127.0.0.1");
    ui->port->setText("8989");
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    // 创建线程对象
    QThread* t = new QThread;
    // 创建任务对象
    SendFile* work = new SendFile;
    // 将任务放到线程对象内
    work->moveToThread(t);
    // 启动子线程
    t->start();

    /*************** 服务器连接 ***************/
    // 点击连接按钮，发送连接信号，传递参数
    connect(ui->connect, &QPushButton::clicked, this, [=] ()
    {
        QString ip = ui->ip->text();
        unsigned short port = ui->port->text().toUShort();
        emit startConnect(ip, port);
    });
    // 信号发送是this对象，信号是startConnect，在主线程
    // 信号处理是work任务对象，槽函数是其中的connectServer，在t线程
    connect(this, &MainWindow::startConnect, work, &SendFile::connectServer);

    /***************** 选择文件 ****************/
    connect(ui->selectFile, &QPushButton::clicked, this, [=] ()
    {
        // 返回用户选择磁盘文件的绝对路径
        QString path = QFileDialog::getOpenFileName();
        if (path.isEmpty())
        {
            QMessageBox::warning(this, "打开文件", "选择的文件路径不能为空");
            return;
        }
        // 将路径显示在文本框内（也是将路径暂存）
        ui->filePath->setText(path);
    });

    /*************** 发送文件 ***************/
    // 点击发送按钮后，通过信号传递文件路径
    connect(ui->sendFile, &QPushButton::clicked, this, [=] ()
    {
        emit sendFile(ui->filePath->text());
    });

    // 子线程任务类对应函数，接收文件发送信号的传过来的路径
    // 并打开相应文件
    connect(this, &MainWindow::sendFile, work, &SendFile::sendFile);


    /************ 处理子线程中任务对象发来的信号 ***********/
    // 根据连接成功信号，输出提示信息
    connect(work, &SendFile::connected, this, [=] ()
    {
        QMessageBox::information(this, "连接服务器", "连接服务器成功！");
        ui->connect->setDisabled(true);
    });
    // 根据断开连接信号回收内存
    connect(work, &SendFile::disconnected, this, [=] ()
    {
        t->quit();
        t->wait();
        work->deleteLater();
        t->deleteLater();
        ui->connect->setEnabled(true);
    });
    // 根据进度信号更新进度条
    connect(work, &SendFile::curPercent, ui->progressBar, &QProgressBar::setValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

