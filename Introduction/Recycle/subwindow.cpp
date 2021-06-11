#include "subwindow.h"
#include "ui_subwindow.h"
#include <QDebug>

// SubWindow是QDialog的子类
// QDialog是QWidget的子类
// QWidget是QObject的子类
SubWindow::SubWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubWindow)
{
    ui->setupUi(this);
}

SubWindow::~SubWindow()
{
    // 打印需要导入头文件<QDebug>，调用宏函数qDebug()
    qDebug() <<  "我是SubWindow，我被析构了...";
    delete ui;
}
