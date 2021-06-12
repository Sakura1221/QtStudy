#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QRunnable>
#include <QThread>
#include <QVector>

// 生成随机数任务类，继承QRunnable，变成能在线程池内执行的任务类
// 继承自QObject，方便使用信号槽，以及Qt自己的内存回收
class Generate : public QObject, public QRunnable
{
    Q_OBJECT
public:
    // 这里传入的参数还是QObject，方便接收任意类型对象
    // 但是继承的父类是QThread，要用QThread的构造函数
    explicit Generate(QObject *parent = nullptr);

    void recvNum(int num);

    // 重载纯虚函数run()，后面加上override
    // run()是一个public的函数
    void run() override;
signals:
    // 向主线程发送数据
    void sendArray(QVector<int>);
private:
    int m_num;
};


class BubbleSort : public QObject, public QRunnable
{
    Q_OBJECT
public:
    // 派生类使用基类构造函数，必须explicit显式声明
    explicit BubbleSort(QObject *parent = nullptr);

    void recvArray(QVector<int> list);

    // 重载纯虚函数run()，后面加上override
    // run()是一个public的函数
    void run() override;

signals:
    // 执行完毕后也需要发送数据
    void finish(QVector<int> num);

private:
    QVector<int> m_list;
};

class QuickSort : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);

    void recvArray(QVector<int> list);

    // 重载纯虚函数run()，后面加上override
    // run()是一个public的函数
    void run() override;

private:
    void quickSort(int l, int r);
signals:
    // 执行完毕后也需要发送数据
    void finish(QVector<int> num);

private:
    QVector<int> m_list;
};

#endif // MYTHREAD_H
