#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* 方式一：setIcon() */
    // 普通按钮，没有checked属性
    ui->normalBtn->setText("我是张三");
    ui->normalBtn->setIcon(QIcon(":/resources/qt.png"));
    ui->normalBtn->setIconSize(QSize(50, 50));
    connect(ui->normalBtn, &QToolButton::clicked, this, [=] ()
    {
        qDebug() << "我是一个普通按钮，名字是张三";
    });
    // 按钮默认只显示图标，设置图标属性，将标题显示在图标右侧
    // 注意设置布局，避免显示不全的情况
    ui->normalBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    /* 方式二：setDefaultAction() */
    // 图标，标题
    QAction* actBtn = new QAction(QIcon(":/resources/qt.png"), "我是张三");
    // 设置toolButton的默认按钮
    ui->actionBtn->setDefaultAction(actBtn);
    // 当toolButton被按下后修改图标和标题
    connect(ui->actionBtn, &QToolButton::triggered, this, [=] (QAction* act)
    {
        act->setText("我是史努比");
        act->setIcon(QIcon(":/resources/snoopy.jpg"));
    });
    ui->actionBtn->setIconSize((QSize(50, 50)));
    ui->actionBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    /* 方式三：setArrowType() */
    ui->arrowBtn->setArrowType(Qt::UpArrow);
    ui->arrowBtn->setText("向上");
    ui->arrowBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    // 有checked属性的按钮
    ui->checkedBtn->setCheckable(true);
    connect(ui->checkedBtn, &QToolButton::toggled, this, [=] (bool st)
    {
        qDebug() << "我是一个checked按钮，当前状态为：" << st;
    });

    // 将按钮与菜单关联，与PushButton不同，菜单是延迟显示的
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

    ui->popmenu->setMenu(menu);
    /* 三种菜单弹出方式，三种枚举类型
        - QToolButton::DelayedPopup: （默认）延迟弹出，按压工具按钮一段时间后才能弹出，比如：浏览器的返回按钮
                                                               长按按钮菜单弹出，但是按钮的clicked信号不会被发射
        - QToolButton::MenuButtonPopup: 工具按钮会显示一个特殊的箭头，表示有菜单。
                                                                      当按下按钮的箭头部分时，将显示菜单。按下按钮部分发射clicked信号
        - QToolButton::InstantPopup: 当按下工具按钮时，菜单立即显示出来。
                                                            在这种模式下，按钮本身的动作不会被出发（不会发射clicked信号）
    */

    ui->popmenu->setPopupMode(QToolButton::MenuButtonPopup);
    connect(ui->popmenu, &QToolButton::clicked, this, [=] ()
    {
        qDebug() << "我是popMenu按钮...";
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

