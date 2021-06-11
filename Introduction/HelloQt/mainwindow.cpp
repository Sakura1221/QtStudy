#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "testwidget.h"
#include "testdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // 实例化UI内的窗口对象并传给ui指针
{
    ui->setupUi(this); // 将ui指向的对象传递给当前对象（实现不同命名空间下同名类对象的捆绑）

    // 一般在qt的构造函数中进行初始化操作（窗口，数据，...）
    // 显示当前窗口的时候，显示另一个窗口TestWidget
#if 1
    // 创建窗口对象，没有给w对象制定父对象，这个窗口是一个独立窗口，有边框
    TestWidget* w = new TestWidget;
    // 要显示当前窗口，必须要单独调用show方法
    w->show();
#else
    // 创建窗口对象，给w对象指定父对象，这里指定为MainWindow窗口对象
    // explicit TestWidget(QWidget *parent = nullptr);
    TestWidget* w = new TestWidget(this);
    // 相当于窗口被内嵌到MainWindow窗口内了（无边框），不需要单独调用show
#endif

#if 0
    // 创建对话框窗口（有无父对象均可）
    TestDialog* dlg = new TestDialog(this);
    // 非模态显示（可以切换窗口）
    dlg->show();
#else
    TestDialog* dlg = new TestDialog(this);
    // 模态显示
    // 阻塞程序的执行（不能切换窗口，除非关闭）
    dlg->exec();
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

