#include "mainwindow.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 主窗口显示前先显示登录窗口（模态阻塞主窗口）
    Login login;
    login.exec();

    MainWindow w;
    w.show();
    // 如果要关闭窗口，就return 0;
    return a.exec();
}
