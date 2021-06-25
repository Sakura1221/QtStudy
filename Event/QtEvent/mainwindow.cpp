#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRandomGenerator>
#include <QMessageBox>
#include <QDebug>
#include "butterfly.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 去掉主窗口边框
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    // 设置主窗口透明
    setAttribute(Qt::WA_TranslucentBackground);
    // 窗口最大化显示
    showMaximized();

    // 创建20只蝴蝶
    for (int i = 0; i < 100; i ++)
    {
        Butterfly* win = new Butterfly(this); // QWidget类型窗口指定了父窗口，不带边框
        win->move(QRandomGenerator::global()->bounded(this->width()),
                            QRandomGenerator::global()->bounded(this->height()));
        win->show(); // 设置了透明，要手动调用show显示
    }

//    // 自定义控件，需要重写信号
//    connect(ui->button, &MyButton::clicked, this, [=]()
//    {
//        QMessageBox::information(this, "按钮", "好痒，不要调戏我...");
//    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *ev)
{
    int ret = QMessageBox::question(this, "提问", "您确定要关闭窗口吗？");
    if (ret == QMessageBox::Yes)
    {
        ev->accept();
    }
    else
    {
        ev->ignore();
    }
}

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    qDebug() << "oldSize: " << ev->oldSize() << "currSize: " << ev->size();
}

