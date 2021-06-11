#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "me.h"
#include "girlfriend.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 添加hungry按钮的槽函数，参数与信号参数保持一致，至少不能多
    void hungrySlot();
    void eatSlot();

private:
    Ui::MainWindow *ui;

    Me* m_me;
    GirlFriend* m_girl;
};
#endif // MAINWINDOW_H
