#ifndef BUTTERFLY_H
#define BUTTERFLY_H

#include <QWidget>
#include <QPainter>

class Butterfly : public QWidget
{
    Q_OBJECT
public:
    explicit Butterfly(QWidget *parent = nullptr);

    void  fly();
    void fly(int min, int max);

protected:
    void paintEvent(QPaintEvent *ev) override;
    void timerEvent(QTimerEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void enterEvent(QEvent *ev) override;

signals:

private:
    QPixmap m_pixmap;
    int m_index = 1;

    QPoint m_pt;
};

#endif // BUTTERFLY_H
