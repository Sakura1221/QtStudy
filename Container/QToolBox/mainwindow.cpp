#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 两种实现效果相同，都是设置默认显示的工具栏
    ui->toolBox->setCurrentIndex(1);
    //ui->toolBox->setCurrentWidget(ui->subwidget2);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_toolBox_currentChanged(int index)
{
    qDebug() << ui->toolBox->itemText(index);
}
