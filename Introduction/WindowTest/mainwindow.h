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
    void on_moveBtn_clicked();

    void on_PositionBtn_clicked();

    void on_geometryBtn_clicked();

    void on_modifyBtn_clicked();

    void on_modalDlg_clicked();

    void on_msgbox_clicked();

    void on_filedlg_clicked();

    void on_fontdlg_clicked();

    void on_colordlg_clicked();

    void on_inputdlg_clicked();

    void on_progressdlg_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
