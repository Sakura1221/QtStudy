#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //唐僧有3个徒弟，分别是孙悟空，猪八戒，沙僧
    QString str = QString("%1有%2个徒弟，分别是%3，%4，%5")
            .arg("唐僧").arg(3).arg("孙悟空").arg("猪八戒").arg("沙僧");
    qDebug() << "字符串的值： " << str;

    // 计算对象中字符串的长度
    QString tmp = "我很帅";
    QByteArray tmp1 = "我很帅";

    qDebug() << "QString length: " << tmp.length(); // 统计字符数
    qDebug() << "QByteArray length: " << tmp1.length(); // 统计字节数，一个汉字3字节
}

MainWindow::~MainWindow()
{
    delete ui;
}

