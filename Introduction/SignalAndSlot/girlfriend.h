#ifndef GIRLFRIEND_H
#define GIRLFRIEND_H

#include <QObject>

class GirlFriend : public QObject
{
    Q_OBJECT
public:
    explicit GirlFriend(QObject *parent = nullptr);

signals:
    // 信号函数只声明不定义
    void hungry();
    void hungry(QString msg);
};

#endif // GIRLFRIEND_H
