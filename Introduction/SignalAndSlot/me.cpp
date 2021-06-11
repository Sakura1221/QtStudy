#include "me.h"
#include <QDebug>

Me::Me(QObject *parent) : QObject(parent)
{

}

void Me::eat()
{
    qDebug() << "我带你去吃麻辣烫...";
}

void Me::eat(QString msg)
{
    qDebug() << "我带你去吃：" << msg;
}
