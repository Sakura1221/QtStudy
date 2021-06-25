#include "butterfly.h"

#include <QDesktopWidget>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QApplication>

Butterfly::Butterfly(QWidget *parent) : QWidget(parent)
{
    m_pixmap.load(":/1");

     setFixedSize(m_pixmap.size());

     startTimer(100); // 定时100ms
}

void Butterfly::fly()
{
    m_index ++;
    if (m_index > 2) m_index = 1;
    QString name = QString(":/%1").arg(m_index);
    m_pixmap.load(name);
    update();

    // 随机移动值[10, 30)
    int stepX = QRandomGenerator::global()->bounded(10, 30);
    int stepY = QRandomGenerator::global()->bounded(10, 30);

    // 当前窗口的全局坐标值（左上角）
    int curX = this->geometry().topLeft().x() + stepX;
    int curY = this->geometry().topLeft().y() + stepY;

    QDesktopWidget *desktop = QApplication::desktop(); // 调用QApplication的静态方法，获取全局窗口对象
    if (curX >= desktop->screenGeometry().right())
    {
        curX = desktop->screenGeometry().left();
    }
    if (curY >= desktop->screenGeometry().bottom())
    {
        curY = desktop->screenGeometry().top();
    }

    move(curX, curY);
}

void Butterfly::fly(int min, int max)
{
    m_index ++;
    if (m_index > 2) m_index = 1;
    QString name = QString(":/%1").arg(m_index);
    m_pixmap.load(name);
    update();

    // 随机移动值[10, 30)
    int stepX = QRandomGenerator::global()->bounded(min, max);
    int stepY = QRandomGenerator::global()->bounded(min, max);

    // 当前窗口的全局坐标值（左上角）
    int curX = this->geometry().topLeft().x() + stepX;
    int curY = this->geometry().topLeft().y() + stepY;

    QDesktopWidget *desktop = QApplication::desktop(); // 调用QApplication的静态方法，获取全局窗口对象
    if (curX >= desktop->screenGeometry().right())
    {
        curX = desktop->screenGeometry().left();
    }
    if (curY >= desktop->screenGeometry().bottom())
    {
        curY = desktop->screenGeometry().top();
    }

    move(curX, curY);
}

void Butterfly::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter p(this);
    p.drawPixmap(rect(), m_pixmap);
}

void Butterfly::timerEvent(QTimerEvent *ev)
{
    Q_UNUSED(ev);
    fly();
}

void Butterfly::mousePressEvent(QMouseEvent *ev)
{
    // 左键被按下，计算按下点与左上角点间的距离
    if (ev->button() == Qt::LeftButton)
    {
        // pos()返回相对坐标，geometry()返回全局坐标，所以这里要用globalPos()
        m_pt = ev->globalPos() - this->geometry().topLeft();
    }
}

void Butterfly::mouseMoveEvent(QMouseEvent *ev)
{
    // 移动过程可能有多个键参与，用buttons()信号
    // 按位与，如果为真，则左键没参与移动
    if (ev->buttons() & Qt::LeftButton)
    {
        this->move(ev->globalPos() - m_pt);
    }
}

// 只在触碰到窗口边缘触发一次，当进入到窗口内部，不再触发
// 若要持续触发，应该一下moveEvent
void Butterfly::enterEvent(QEvent *ev)
{
    fly(-200, 200);
}
