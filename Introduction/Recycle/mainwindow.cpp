#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "subwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SubWindow* sub = new SubWindow(this);
    sub->show(); // 非模态显示
}

MainWindow::~MainWindow()
{
    delete ui;
}

