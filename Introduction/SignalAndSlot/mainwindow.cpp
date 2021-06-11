#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // 将ui指向的对象与当前对象绑定，可以直接调用

    // 初始化成员
    m_me = new Me;
    m_girl = new GirlFriend;

    // 用connect注册信号槽，由操作系统监测信号并处理
    // 信号发出者，发出的信号，信号接收者，槽函数（回调函数）
    //connect(m_girl, &GirlFriend::hungry, m_me, &Me::eat); // 自定义信号与槽函数
    // 如果重载了信号与槽函数，需要在外部指明函数指针
    void (GirlFriend::*girl1)() = &GirlFriend::hungry;
    void (GirlFriend::*girl2)(QString) = &GirlFriend::hungry;
    void (Me::*mypoint)(QString) = &Me::eat;
    connect(m_girl, girl2, m_me, mypoint);
    connect(m_girl, girl2, this, &MainWindow::eatSlot); // 槽函数参数比信号参数少，忽略信号参数
    // 将按钮按下事件与m_girl对象发射hungry信号绑定，这里用hungrySlot槽函数封装
    //connect(ui->hungry, &QPushButton::clicked, this, &MainWindow::hungrySlot);

    // 将上面信号槽的槽函数写成匿名函数
    connect(ui->hungry, &QPushButton::clicked, this, [=] () {
        // 发射自定义信号
        m_girl->hungry();
        m_girl->hungry("意大利面");
    });

    // 使用Qt4的方式进行连接，不是传函数地址，而是用宏函数转换成char*类型
    // 一次连接执行一次槽函数，也就是会执行两次eat
    connect(m_girl, SIGNAL(hungry()), m_me, SLOT(eat()));
    connect(m_girl, SIGNAL(hungry(QString)), m_me, SLOT(eat(QString)));

    // 信号连接信号，不用将发射信号单独定义成一个槽函数
    //connect(ui->hungry, &QPushButton::clicked, m_girl, &GirlFriend::hungry);
    // 信号与当前对象建立连接
    //connect(m_girl, &GirlFriend::hungry, this, &MainWindow::eatSlot);

    connect(ui->closeBtn, &QPushButton::clicked, this, &MainWindow::close);

    // 匿名函数的定义
    [] () {
        qDebug() << "hello, 我是一个lambda表达式...";
    };

    // 调用匿名函数
    int a = 100, b = 200, c = 300;
    // 传引用方式使用外部数据
    [&] ( ) {
            qDebug() << "hello, 我是一个lambda表达式...";
            qDebug() << "使用引用的方式传递数据： ";
            qDebug() << "a + 1:" << ++a << ", b + c =  " << b + c;
    }();

    // 传拷贝方式使用外部数据
    [=] (int m, int n ) mutable {
            qDebug() << "hello, 我是一个lambda表达式...";
            qDebug() << "使用引用的方式传递数据： ";
            // 拷贝的外部数据在函数体内部是只读的，加上mutable才可写
            qDebug() << "a + 1:" << ++a << ", b + c =  " << b + c;
            qDebug() << "m + 1: " << ++m << ", n + 1 = " << ++n;
    }(1, 2);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hungrySlot()
{
    // 发射自定义信号
    emit m_girl->hungry();
    emit m_girl->hungry("意大利面");
}

void MainWindow::eatSlot()
{
    qDebug() << "我带你去吃海鲜...";
}

