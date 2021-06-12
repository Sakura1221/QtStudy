#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 用信号槽实现主线程与子线程的通信，某些数据类型需要先注册
    // 这是一个类模板，需要传入待注册的类型，参数是类型字符串
    qRegisterMetaType<QVector<int>>("QVector<int>");
    MainWindow w;
    w.show();
    return a.exec();
}
