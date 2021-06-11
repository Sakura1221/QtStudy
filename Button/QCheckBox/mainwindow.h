#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_cpp_stateChanged(int arg1);

    void on_go_stateChanged(int arg1);

    void on_python_stateChanged(int arg1);

    void on_java_stateChanged(int arg1);

    // 信号会发出一个int类型的参数
    void statusChanged(int state);

private:
    Ui::MainWindow *ui;
    int m_number = 0;
};
#endif // MAINWINDOW_H
