#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置根结点的三态属性
    ui->wives->setTristate(true);

    // 当父结点状态改变后，子结点也要相应改变（只有全选或全未选两种状态）
    // 为了避免信号冲突，捕获clicked信号
    // 需要判断按钮是否被选中了，这里要传入clicked信号返回值
    connect(ui->wives, &QCheckBox::clicked, this, [=] (bool st)
    {
        if (st)
        {
            ui->jianning->setChecked(true);
            ui->fangyi->setChecked(true);
            ui->longer->setChecked(true);
            ui->zengrou->setChecked(true);
            ui->mujianping->setChecked(true);
            ui->shuanger->setChecked(true);
            ui->ake->setChecked(true);
        }
        else
        {
            ui->jianning->setChecked(false);
            ui->fangyi->setChecked(false);
            ui->longer->setChecked(false);
            ui->zengrou->setChecked(false);
            ui->mujianping->setChecked(false);
            ui->shuanger->setChecked(false);
            ui->ake->setChecked(false);
        }
    });

    // 信号与槽函数都相同，要使用统一函数，槽函数不能是匿名函数
    connect(ui->jianning, &QCheckBox::stateChanged, this, &MainWindow::statusChanged);
    connect(ui->fangyi, &QCheckBox::stateChanged, this, &MainWindow::statusChanged);
    connect(ui->longer, &QCheckBox::stateChanged, this, &MainWindow::statusChanged);
    connect(ui->zengrou, &QCheckBox::stateChanged, this, &MainWindow::statusChanged);
    connect(ui->mujianping, &QCheckBox::stateChanged, this, &MainWindow::statusChanged);
    connect(ui->shuanger, &QCheckBox::stateChanged, this, &MainWindow::statusChanged);
    connect(ui->ake, &QCheckBox::stateChanged, this, &MainWindow::statusChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_cpp_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        qDebug() << "我会C++";
    }
    else
    {
        qDebug() << "我不会C++";
    }
}

void MainWindow::on_go_stateChanged(int arg1)
{
    // 选中时
    if (arg1 == Qt::Checked)
    {
        qDebug() << "我会Go";
    }
    // 取消时
    else
    {
        qDebug() << "我不会Go";
    }
}

void MainWindow::on_python_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        qDebug() << "我会Python";
    }
    else
    {
        qDebug() << "我不会Python";
    }
}

void MainWindow::on_java_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        qDebug() << "我会Java";
    }
    else
    {
        qDebug() << "我不会Java";
    }
}

void MainWindow::statusChanged(int state)
{
    // 子结点状态修改计数器
    if (state == Qt::Checked)
    {
        m_number ++;
    }
    else
    {
        m_number --;
    }

    // 根据计数器修改根结点状态
    if (m_number == 7)
    {
        ui->wives->setCheckState(Qt::Checked);
    }
    else if (m_number == 0)
    {
        ui->wives->setCheckState(Qt::Unchecked);
    }
    else
    {
        ui->wives->setCheckState(Qt::PartiallyChecked);
    }
}
