#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->move(10, 10);

    // 创建一个按钮，让这个按钮作为当前创建窗口的子控件
    QPushButton* btnA = new QPushButton(this);
    // 移动按钮的位置
    btnA->move(10, 10);
    // 给按钮设置固定大小
    btnA->setFixedSize(200, 200);


    // 创建一个按钮，让这个按钮作为当前创建窗口的子控件
    QPushButton* btnB = new QPushButton(btnA);
    // 移动按钮的位置
    btnB->move(10, 10);
    // 给按钮设置固定大小
    btnB->setFixedSize(100, 100);

    // 创建一个按钮，让这个按钮作为当前创建窗口的子控件
    QPushButton* btnC = new QPushButton(btnB);
    // 移动按钮的位置
    btnC->move(10, 10);
    // 给按钮设置固定大小
    btnC->setFixedSize(50, 50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

