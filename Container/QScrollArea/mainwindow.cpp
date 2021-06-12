#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 在滚动区域设置新的窗口，用来显示图片
    // 内部的content无效（不显示），且只能设置一个窗口
    //QLabel* pic = new QLabel;
    // 想要显示多个窗口，需要在唯一窗口内用布局实现
    // 创建一个垂直布局
    QVBoxLayout* vlayout = new QVBoxLayout;
    for (int i = 0; i < 2; i ++)
    {
        QLabel* pic = new QLabel;
        QString file = QString(":/resources/%1.png").arg(i + 1);
        pic->setPixmap(QPixmap(file));
        pic->setAlignment(Qt::AlignHCenter);
        vlayout->addWidget(pic);
    }

    // 滚动区域内唯一窗口对象内添加布局
    QWidget* wg = new QWidget;
    wg->setLayout(vlayout);
    ui->scrollArea->setWidget(wg);

//    pic->setPixmap(QPixmap(":/resources/1.png"));
//    // 窗口默认充满滚动区域（一样大）
//    ui->scrollArea->setWidget(pic);
//    pic->setFixedWidth(600);
//    // 将label对象居中（不是将图片居中）
//    ui->scrollArea->setAlignment(Qt::AlignHCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

