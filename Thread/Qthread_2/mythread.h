#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>

// 生成随机数任务类，必须继承QObject
class Generate : public QObject
{
    Q_OBJECT
public:
    // 这里传入的参数还是QObject，方便接收任意类型对象
    // 但是继承的父类是QThread，要用QThread的构造函数
    explicit Generate(QObject *parent = nullptr);

    // run函数不能传参，且函数名固定
    // 这种方式函数名可以任意指定，且可传参
    void working(int num);

signals:
    // 向主线程发送数据
    void sendArray(QVector<int>);
};


class BubbleSort : public QObject
{
    Q_OBJECT
public:
    // 派生类使用基类构造函数，必须explicit显式声明
    explicit BubbleSort(QObject *parent = nullptr);

    void working(QVector<int> list);

signals:
    // 执行完毕后也需要发送数据
    void finish(QVector<int> num);
};

class QuickSort : public QObject
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);

    void working(QVector<int> list);

private:
    void quickSort(QVector<int> &list, int l, int r);

signals:
    // 执行完毕后也需要发送数据
    void finish(QVector<int> num);
};

#endif // MYTHREAD_H
