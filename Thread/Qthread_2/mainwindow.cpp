#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1.创建子线程对象
    // 不能指定父对象，不能调用Qt自己的内存回收
    // 不想设置成成员变量，调用析构函数析构
    // 可以用信号槽机制回收内存
    QThread* t1 = new QThread;
    QThread* t2 = new QThread;
    QThread* t3 = new QThread;

    // 2.创建任务类对象
    // 必须是QObject类的子类，才能有moveToThread方法
    // 不能指定父对象，不然就不能移动到子线程内了
    Generate* gen = new Generate;
    BubbleSort* bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;

    // 3.将任务对象移动到某个子线程中
    gen->moveToThread(t1);
    bubble->moveToThread(t2);
    quick->moveToThread(t3);

    // 任务函数可以代替槽函数接收数据
    // 可以通过connect信号发出对象与接收对象是否在同一个线程，判断是否为多线程执行
    // 槽函数只能调用接收对象同一线程内的对象
    connect(this, &MainWindow::starting, gen, &Generate::working);
    // 2.向子线程发送数据，并启动子线程
    // 启动前已经生成对象，可接收数据
    // 按下开始按钮后，启动子线程（调用子线程的start方法）
    connect(ui->start, &QPushButton::clicked, this, [=] ()
    {
        // 启动前先向子线程发送数据
        // 设置一个带参数的信号，子线程内的recvNum槽函数可以接收参数（数据）
        emit starting(10000);
        t1->start();
    });

    // 3.其他线程接收线程发送的数据，对数据进行显示或处理
    // 排序线程排序，里面有recvArray()槽函数可以接收数据（只用写函数名）
    connect(gen, &Generate::sendArray, bubble, &BubbleSort::working);
    connect(gen, &Generate::sendArray, quick, &QuickSort::working);

    // 主线程接收，用randList显示
    connect(gen, &Generate::sendArray, this, [=] (QVector<int> list)
    {
        // 启动两个子线程进行排序，相当于通过主线程实现了子线程间的同步
        t2->start();
        t3->start();
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

    // 利用信号槽回收内存，当主窗口销毁时，回收内存
    connect(this, &MainWindow::destroyed, this, [=] ()
    {
        t1->quit();
        t1->wait();
        t1->deleteLater(); // delete t1;

        t2->quit();
        t2->wait();
        t2->deleteLater(); // delete t1;

        t3->quit();
        t3->wait();
        t3->deleteLater(); // delete t1;

        gen->deleteLater();
        bubble->deleteLater();
        quick->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

