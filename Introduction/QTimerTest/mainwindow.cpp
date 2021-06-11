#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建定时器对象
    QTimer* timer = new QTimer(this);

    //  修改定时器对象的精度
    timer->setTimerType(Qt::PreciseTimer);

    // 按钮的点击事件
    connect(ui->loopBtn, &QPushButton::clicked, this, [=] ()
    {
        //  启动定时器
        if (timer->isActive())
        {
            timer->stop(); // 关闭定时器
            ui->loopBtn->setText("开始"); // 控件显示重置为开始
        }
        else
        {
            ui->loopBtn->setText("关闭"); // 控件显示变成关闭
            timer->start(1000); // 1000ms = 1s
        }
    });

    connect(timer, &QTimer::timeout, this, [=] ()
    {
        QTime tm = QTime::currentTime();
        // 格式化此时的系统时间
        QString tmstr = tm.toString("hh:mm:ss.zzz");
        // 设置要显示的时间
        ui->curTime->setText(tmstr);
    });

    // 发射一次信号
    connect(ui->onceBtn, &QPushButton::clicked, this, [=] ()
    {
        // 获取2s以后的系统时间
        QTimer::singleShot(2000, this, [=] ()
        {
            QTime tm = QTime::currentTime();
            // 格式化此时的系统时间
            QString tmstr = tm.toString("hh:mm:ss.zzz");
            // 设置要显示的时间
            ui->onceTime->setText(tmstr);
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

