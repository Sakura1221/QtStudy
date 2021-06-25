#include "mybutton.h"

MyButton::MyButton(QWidget *parent) : QWidget(parent)
{
    m_pixmap.load(":/ghost-1.png"); // 默认为1
    setFixedSize(m_pixmap.size()); // 窗口大小与图片大小相同
}

void MyButton::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
     m_pixmap.load(":/ghost-2.png"); // 点击为2
     update(); // QWidget类的槽函数，调用后会触发绘图事件（刷新窗口）
     emit clicked();
     // 执行完子类的事件处理动作，还可以继续执行父类的事件处理动作
     // 比如继承了QPushButton()，执行父类的处理动作，才能发出相关信号
     // QWidget::mousePressEvent(ev);
}

void MyButton::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    m_pixmap.load(":/ghost-1.png"); // 释放恢复
    update();
}

void MyButton::enterEvent(QEvent *ev)
{
    Q_UNUSED(ev);
     m_pixmap.load(":/ghost-3.png"); // 鼠标悬停（进入）为3
     update();
}

void MyButton::leaveEvent(QEvent *ev)
{
    Q_UNUSED(ev);
    m_pixmap.load(":/ghost-1.png"); // 离开恢复
    update();
}

void MyButton::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter p(this); // 指定作图设备（画在当前窗口）
    p.drawPixmap(rect(), m_pixmap); // 将图片对象m_pixmap画到当前窗口的矩形区域rect()
}
