#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 默认显示tab2
    ui->stackedWidget->setCurrentWidget(ui->page_2);

    // 栈窗口需要额外设置按钮进行页面切换
    connect(ui->win1, &QPushButton::clicked, this, [=] ()
    {
        // setCurrentIndex选择当前显示页面
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->win2, &QPushButton::clicked, this, [=] ()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_2);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

