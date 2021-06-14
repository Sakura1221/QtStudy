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

signals:
    // 函数声明时可不写参数名，只写参数类型
    void startConnect(QString, unsigned short);
    void sendFile(QString);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
