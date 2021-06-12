#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 当标签页关闭按钮被按下时，关闭标签页，保存信息供恢复
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, [=] (int index)
    {
        // 保存信息
        QWidget* wg = ui->tabWidget->widget(index); // widget返回标签页对象
        QString title = ui->tabWidget->tabText(index);
        // enqueue是向队尾插入数据
        m_widgets.enqueue(wg);
        m_titles.enqueue(title);

        // 移除标签页
        ui->tabWidget->removeTab(index);
        // 恢复按钮状态变成可用
        ui->addBtn->setEnabled(true);
    });

    // 当标签页被点击了
    connect(ui->tabWidget, &QTabWidget::tabBarClicked, this, [=] (int index)
    {
        qDebug() << "我被点击了一下，我的标题是：" << ui->tabWidget->tabText(index);
    });

    // 显示的标签页发生改变
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, [=] (int index)
    {
        qDebug() << "当前显示的标签页的标题是：" << ui->tabWidget->tabText(index);
    });

    // 添加标签页按钮，将被删除的标签页加到窗口中
    connect(ui->addBtn, &QPushButton::clicked, this, [=] ()
    {
        // 1.窗口对象，窗口标题
        // 2.添加函数
        // dequeue()是从队头取数据
        ui->tabWidget->addTab(m_widgets.dequeue(), m_titles.dequeue());
        // 队列无数据，按钮不可用
        if (m_widgets.empty())
        {
            ui->addBtn->setDisabled(true);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

