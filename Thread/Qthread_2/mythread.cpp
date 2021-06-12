#include "mythread.h"
#include <QElapsedTimer>
#include <QDebug>

// 继承和传参都是QObject
Generate::Generate(QObject *parent) : QObject(parent)
{

}

void Generate::working(int num)
{
    qDebug() << "生成随机数线程的地址" << QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for (int i = 0; i < num; i ++)
    {
        list.push_back(qrand() % 100000);
    }
    int msec = time.elapsed();
    qDebug() << "生成" << num << "个随机数总共用时:" << msec  << "毫秒";
    // 用槽函数向主线程发送数据
    emit sendArray(list);
}

// 派生类调用基类构造函数，不要忘记将参数传入构造
BubbleSort::BubbleSort(QObject *parent) : QObject(parent)
{

}

void BubbleSort::working(QVector<int> list)
{
    qDebug() << "冒泡排序线程的地址" << QThread::currentThread();
    QElapsedTimer time;
    time.start();

    for (int i = 0; i < list.size(); i ++)
        for (int j = 0; j < list.size() - i - 1; j ++)
            if (list[j] > list[j + 1])
                qSwap(list[j], list[j + 1]);

    int msec = time.elapsed();
    qDebug() << "冒泡排序用时:" << msec  << "毫秒";
    // 用槽函数向主线程发送数据
    emit finish(list);
}


// 派生类调用基类构造函数，不要忘记将参数传入构造
QuickSort::QuickSort(QObject *parent) : QObject(parent)
{

}

void QuickSort::working(QVector<int> list)
{
    qDebug() << "快速排序线程的地址" << QThread::currentThread();
    QElapsedTimer time;
    time.start();

    quickSort(list, 0, list.size() - 1);

    int msec = time.elapsed();
    qDebug() << "快速排序用时:" << msec  << "毫秒";
    // 用槽函数向主线程发送数据
    emit finish(list);
}

void QuickSort::quickSort(QVector<int> &list, int l, int r)
{
    if (l >= r) return;

    int x = list[(l + r) >> 1], i = l - 1, j = r + 1;
    while (i < j)
    {
        while (list[++ i] < x);
        while (list[-- j] > x);
        if (i < j) qSwap(list[i], list[j]);
    }

    quickSort(list, l, j);
    quickSort(list, j + 1, r);
}
