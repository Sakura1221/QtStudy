#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLine line(QPoint(100, 200), QPoint(150, 210));
    QLine newLine = line.translated(20, 20);
    qDebug() << "平移之前的端点： " << line;
    qDebug() << "平移之后的端点： " << newLine;
}

MainWindow::~MainWindow()
{
    delete ui;
}

