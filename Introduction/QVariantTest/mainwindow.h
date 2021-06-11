#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// 自定义数据类型
struct Person
{
    int id;
    QString name;
};

// 在qt中声明自定义数据类型
Q_DECLARE_METATYPE(Person)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 两个变量进行加法运算，变量可能是整形，也可能是字符串
    QVariant dataPlus(QVariant a, QVariant b);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
