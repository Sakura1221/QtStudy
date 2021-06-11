#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 通过setchecked方法设置默认选项
    ui->radioButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_radioButton_clicked()
{
    qDebug() << "C++";
}

void MainWindow::on_radioButton_2_clicked()
{
    qDebug() << "Go";
}

void MainWindow::on_radioButton_3_clicked()
{
    qDebug() << "Python";
}

void MainWindow::on_radioButton_4_clicked()
{
    qDebug() << "Java";
}
