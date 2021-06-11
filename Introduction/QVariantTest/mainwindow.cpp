#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 此处用到了c++中的隐式类型转换
    // 整形数
    int value = dataPlus(10, 20).toInt();
    // 字符串
    QString str = dataPlus("hello ", "world").toString();

    qDebug() << "int value: " << value;
    qDebug() << "string value: " << str;

    // 创建Person对象
    Person p;
    p.id = 250;
    p.name = "张三丰";
// 将自定义数据类型转换成QVariant对象，有两种方法
// 成员方法
#if 0
    QVariant v;
    v.setValue(p);
#else
// 静态方法
    QVariant v = QVariant::fromValue(p);
#endif

    // 取出v对象中的数据，用canConvert对数据类型进行转换
    if (v.canConvert<Person>())
    {
        Person tmp = v.value<Person>();
        qDebug() << "id: " << tmp.id << ", name: "  << tmp.name;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVariant MainWindow::dataPlus(QVariant a, QVariant b)
{
    QVariant ret;
    // 判断当前参数的类型是字符串还是整形数
    if (a.type() == QVariant::Int && b.type() == QVariant::Int)
    {
        ret = QVariant(a.toInt() + b.toInt());
    }
    else if (a.type() == QVariant::String && b.type() == QVariant::String)
    {
        ret.setValue(a.toString() + b.toString());
    }
    return ret;
}

