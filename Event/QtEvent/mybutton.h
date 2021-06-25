#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPainter>

class MyButton : public QWidget
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
    void enterEvent(QEvent* ev);
    void leaveEvent(QEvent* ev);
    void paintEvent(QPaintEvent* ev); // 窗口需要被刷新时，自动被调用

signals:
    void clicked();

private:
    QPixmap m_pixmap; // 显示更好
    // QImage m_imag; // 传输更好，支持逐像素修改
};

#endif // MYBUTTON_H
