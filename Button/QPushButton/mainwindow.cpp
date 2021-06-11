#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 普通按钮，没有checked属性
    ui->normalBtn->setText("我是张三");
    ui->normalBtn->setIcon(QIcon(":/resources/qt.png"));
    ui->normalBtn->setIconSize(QSize(30, 30));
    connect(ui->normalBtn, &QPushButton::clicked, this, [=] ()
    {
        qDebug() << "我是一个普通按钮，名字是张三";
    });

    // 有checked属性的按钮
    ui->checkedBtn->setCheckable(true);
    connect(ui->checkedBtn, &QPushButton::toggled, this, [=] (bool st)
    {
        qDebug() << "我是一个checked按钮，当前状态为：" << st;
    });

    // 将按钮与菜单关联
    ui->menuBtn->setText("喜欢哪种美女？");
    // 菜单内添加一些动作
    QMenu* menu = new QMenu;
    QAction* act1 = menu->addAction("可爱的");
    QAction* act2 = menu->addAction("粘人的");
    QAction* act3 = menu->addAction("漂亮的");
    QAction* act4 = menu->addAction("性感的");
    ui->menuBtn->setMenu(menu);
    // 动作被选择会发出triggered信号
    connect(act1, &QAction::triggered, this, [=] ()
    {
        qDebug() << "我是一个可爱的女人...";
    });
    connect(act2, &QAction::triggered, this, [=] ()
    {
        qDebug() << "我是一个粘人的女人...";
    });
    connect(act3, &QAction::triggered, this, [=] ()
    {
        qDebug() << "我是一个漂亮的女人...";
    });
    connect(act4, &QAction::triggered, this, [=] ()
    {
        qDebug() << "我是一个性感的女人...";
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

