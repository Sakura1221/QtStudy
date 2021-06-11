#ifndef ME_H
#define ME_H

#include <QObject>

class Me : public QObject
{
    Q_OBJECT
public:
    explicit Me(QObject *parent = nullptr);

public slots:
    // 槽函数要定义
    void eat();
    void eat(QString msg);
};

#endif // ME_H
