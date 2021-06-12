#include "mythread.h"
#include <QElapsedTimer>
#include <QDebug>

// 注意继承的是QThread，传的是QObject，调用QThread的构造函数
Generate::Generate(QObject *parent) : QObject(parent), QRunnable()
{
    // 设置线程自动回收内存
    setAutoDelete(true);
}

void Generate::recvNum(int num)
{
    m_num = num;
}

void Generate::run()
{
    qDebug() << "生成随机数线程的地址" << QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for (int i = 0; i < m_num; i ++)
    {
        list.push_back(qrand() % 100000);
    }
    int msec = time.elapsed();
    qDebug() << "生成" << m_num << "个随机数总共用时:" << msec  << "毫秒";
    // 用槽函数向主线程发送数据
    emit sendArray(list);
}

// 派生类调用基类构造函数，不要忘记将参数传入构造
BubbleSort::BubbleSort(QObject *parent) : QObject(parent), QRunnable()
{
    // 设置线程自动回收内存
    setAutoDelete(true);
}


void BubbleSort::recvArray(QVector<int> list)
{
    m_list = list;
}

void BubbleSort::run()
{
    qDebug() << "冒泡排序线程的地址" << QThread::currentThread();
    QElapsedTimer time;
    time.start();

    for (int i = 0; i < m_list.size(); i ++)
        for (int j = 0; j < m_list.size() - i - 1; j ++)
            if (m_list[j] > m_list[j + 1])
                qSwap(m_list[j], m_list[j + 1]);

    int msec = time.elapsed();
    qDebug() << "冒泡排序用时:" << msec  << "毫秒";
    // 用槽函数向主线程发送数据
    emit finish(m_list);
}


// 派生类调用基类构造函数，不要忘记将参数传入构造
QuickSort::QuickSort(QObject *parent) : QObject(parent), QRunnable()
{
    // 设置线程自动回收内存
    setAutoDelete(true);
}


void QuickSort::recvArray(QVector<int> list)
{
    m_list = list;
}

void QuickSort::run()
{
    qDebug() << "快速排序线程的地址" << QThread::currentThread();
    QElapsedTimer time;
    time.start();

    quickSort(0, m_list.size() - 1);

    int msec = time.elapsed();
    qDebug() << "快速排序用时:" << msec  << "毫秒";
    // 用槽函数向主线程发送数据
    emit finish(m_list);
}

void QuickSort::quickSort(int l, int r)
{
    if (l >= r) return;

    int x = m_list[(l + r) >> 1], i = l - 1, j = r + 1;
    while (i < j)
    {
        while (m_list[++ i] < x);
        while (m_list[-- j] > x);
        if (i < j) qSwap(m_list[i], m_list[j]);
    }

    quickSort(l, j);
    quickSort(j + 1, r);
}
