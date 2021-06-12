#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include <QThreadPool>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1.创建任务类对象
    Generate* gen = new Generate;
    BubbleSort* bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;

    // 建立数据发送信号与子线程数据接收槽函数的连接
    connect(this, &MainWindow::starting, gen, &Generate::recvNum);
    // 2.向子线程发送数据，并启动子线程
    // 启动前已经生成对象，可接收数据
    // 按下开始按钮后，启动子线程（调用子线程的start方法）
    connect(ui->start, &QPushButton::clicked, this, [=] ()
    {
        // 启动前先向子线程发送数据
        // 设置一个带参数的信号，子线程内的recvNum槽函数可以接收参数（数据）
        emit starting(10000);
        //  线程池调用接口
        // 将生成随机数任务放到线程池内执行
        QThreadPool::globalInstance()->start(gen);
    });

    // 3.其他线程接收线程发送的数据，对数据进行显示或处理
    // 排序线程排序，里面有recvArray()槽函数可以接收数据（只用写函数名）
    connect(gen, &Generate::sendArray, bubble, &BubbleSort::recvArray);
    connect(gen, &Generate::sendArray, quick, &QuickSort::recvArray);

    // 主线程接收，用randList显示
    connect(gen, &Generate::sendArray, this, [=] (QVector<int> list)
    {
        // 将两个排序任务放到线程池内执行
        QThreadPool::globalInstance()->start(bubble);
        QThreadPool::globalInstance()->start( quick);
        for (int i = 0; i < list.size(); i ++)
        {
            ui->randList->addItem(QString::number(list[i]));
        }
    });

    connect(bubble, &BubbleSort::finish, this, [=] (QVector<int> list)
    {
        for (int i = 0; i < list.size(); i ++)
        {
            ui->bubbleList->addItem(QString::number(list[i]));
        }
    });

    connect(quick, &QuickSort::finish, this, [=] (QVector<int> list)
    {
        for (int i = 0; i < list.size(); i ++)
        {
            ui->quickList->addItem(QString::number(list[i]));
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

