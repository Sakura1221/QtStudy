#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mydialog.h"
#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPainter>
#include <QProgressDialog>
#include <QTimer>
#include <QToolbar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口的最大尺寸
    //setMaximumSize(600, 600);
    // 设置窗口的最小尺寸
    //setMinimumSize(300, 300);
    // 设置窗口的固定尺寸
    //setFixedSize(450, 450);
    // 设置窗口标题
    setWindowTitle("hello, Qt");
    // 给显示的窗口设置图标
    setWindowIcon(QIcon("resources/qt.png"));

    connect(this, &MainWindow::windowTitleChanged, this, [=] (const QString &title)
    {
       qDebug() << "新的标题： " << title;
    });

    connect(this, &MainWindow::windowIconChanged, this, [=] (const QIcon &icon)
    {
       qDebug() << "当前窗口的图标被修改了...";
    });

    setContextMenuPolicy(Qt::CustomContextMenu);
    // 信号发送的是相对窗口的坐标
    connect(this, &MainWindow::customContextMenuRequested, this, [=] (const QPoint &pos)
    {
        QMenu menu;
        menu.addAction("西红柿");
        menu.addAction("黄瓜");
        menu.addAction("茄子");
        // 需要手动调用显示
        // QCursor::pos()返回的是当前光标所在的全局坐标
        menu.exec(QCursor::pos());
    });

    connect(ui->saveAction, &QAction::triggered, this, [=] ()
    {
        QMessageBox::information(this, "clicked", "你不要调戏我...");
    });

    // 给工具栏添加按钮和单行输入框
    ui->toolBar->addWidget(new QPushButton("搜索"));
    QLineEdit* edit = new QLineEdit; // 先new出来方便设置属性
    //edit->setMaximumWidth(200);
    edit->setFixedWidth(100);
    ui->toolBar->addWidget(edit);

    // 添加第二个工具栏
    // 不用指定父对象，谁add谁就是它的父对象
    QToolBar* toolbar = new QToolBar("toolbar");
    // 在第二个工具栏添加动作按钮
    toolbar->addAction(QIcon(":/resources/qt.png"), "打开文件");
    // 位置，工具栏对象
    this->addToolBar(Qt::LeftToolBarArea, toolbar);

    // 两种方式会冲突，显示信息要写在前面，实际开发二选一
    // 要设置定时并手动调用控件的show方法，控件才能显示
    // 方式一：状态栏显示信息
    ui->statusbar->showMessage("我是状态栏...", 2000);
    // 方式二：状态栏添加子控件
    // 按钮
    QPushButton* button = new QPushButton("按钮");
    ui->statusbar->addWidget(button);
    // 标签
    QLabel* label = new QLabel("hello,world");
    ui->statusbar->addWidget(label);

    QTimer::singleShot(5000, this, [=] ()
    {
        button->show();
        label->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_moveBtn_clicked()
{
    QRect rect = this->frameGeometry();
    move(rect.topLeft() + QPoint(10, 20));
}

void MainWindow::on_PositionBtn_clicked()
{
    QRect rect = this->frameGeometry();
    qDebug() << "左上角：" << rect.topLeft()
                      << " 右上角：" << rect.topRight()
                      << " 左下角：" << rect.bottomLeft()
                      << " 右下角：" << rect.bottomRight()
                      << " 宽度：" << rect.width()
                      << " 高度：" << rect.height();
}

void MainWindow::on_geometryBtn_clicked()
{
    int x = 100 + rand() % 500;
    int y = 100 + rand() % 500;
    int width  = this->width()  + 10;
    int height = this->height() + 10;
    setGeometry(x, y, width, height);
}

void MainWindow::on_modifyBtn_clicked()
{
    setWindowTitle("你好，世界");
    setWindowIcon(QIcon("resources/snoopy.jpg"));
}

void MainWindow::on_modalDlg_clicked()
{
    MyDialog dlg;
    connect(&dlg, &MyDialog::finished, this, [=] (int res)
    {
        qDebug() << "result: " << res;
    });
    connect(&dlg, &MyDialog::accepted, this, [=] ()
    {
       qDebug() << "accepted信号被发射了";
    });
    connect(&dlg, &MyDialog::rejected, this, [=] ()
    {
        qDebug() << "rejected信号被发射了";
    });

    int ret = dlg.exec();
    if (ret == QDialog::Accepted)
    {
        qDebug() << "accept button clicked...";
    }
    else if (ret == QDialog::Rejected)
    {
        qDebug() << "reject button clicked...";
    }
    else
    {
        qDebug() << "done button clicked...";
    }
}

void MainWindow::on_msgbox_clicked()
{
    // 父类，标题，内容
    QMessageBox::about(this, "about", "这是一个简单的消息提示框！");
    QMessageBox::critical(this, "critical", "这是一个错误对话框");
    // 多了一个选项，且有返回值
    int ret = QMessageBox::question(this, "question", "你要保存修改的文件内容吗？",
                                    QMessageBox::Save | QMessageBox::Cancel, QMessageBox::Cancel); // 将Yes/No替换成Save/Cancel，默认为Cancel
    if (ret == QMessageBox::Save)
    {
        QMessageBox::information(this, "information", "恭喜你保存成功了!");
    }
    else if (ret == QMessageBox::Cancel)
    {
        QMessageBox::warning(this, "warning", "你取消了保存！");
    }
}

#define SAVEFILE
void MainWindow::on_filedlg_clicked()
{
#ifdef OPENDIR
    // 只显示目录
    // 父窗口，窗口名，初始目录，返回打开的目录
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "resources/");
    // 父窗口，窗口名，内容
    QMessageBox::information(this, "打开目录", "您选择的目录是:" + dirName);
#endif

#ifdef OPENFILE
    QString arg("Text files (*.txt)");
    // 打开单个文件
    // 父窗口，窗口名，初始目录，过滤器，默认过滤器
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open File"), "resources/",
                tr("Images (*.png *.jpg);;Text files (*.txt)"), &arg);
    QMessageBox::information(this, "打开文件", "您选择的文件是：" + fileName);
#endif

#ifdef OPENFILES
    QStringList fileNames = QFileDialog::getOpenFileNames(
                this, tr("Open File"), "C:\\Users\\Sakura\\Desktop\\resources",
                tr("Images (*.png *.jpg);;Text files (*.txt)")); // 未指定过滤器，默认选择第一个
    QString names;
    for (int i = 0; i < fileNames.size(); i ++)
    {
        names += fileNames[i] + " ";
    }
    QMessageBox::information(this, "打开文件(s)", "您选择的文件是：" + names);
#endif

#ifdef SAVEFILE
    // 后续再执行写操作，如果不存在会创建，如果存在会覆盖
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "resources/");
    QMessageBox::information(this, "保存文件", "您指定保存数据的文件是：" + fileName);
#endif
}

void MainWindow::on_fontdlg_clicked()
{
#if 0
    bool ok; // 传出参数，判断是否设置成功
    // 字体对话框，返回创建的字体对象
    QFont ft = QFontDialog::getFont(
                &ok, QFont("Arial", 12, QFont::Bold), this, "选择字体"); // 12号，Arial字体，加粗，父对象，标题
    qDebug() << "ok value is: " << ok;
#else
    QFont ft = QFontDialog::getFont(NULL);
#endif
    // 也可以直接创建字体对象并用setFont设置给窗口
    ui->fontlabel->setFont(ft); // 标签设置字体
}

void MainWindow::on_colordlg_clicked()
{
    QColor color = QColorDialog::getColor();
    QBrush brush(color);
    QRect rect(0, 0, ui->color->width(), ui->color->height());
    QPixmap pix(rect.width(), rect.height());
    QPainter p(&pix);
    p.fillRect(rect, brush);
    ui->color->setPixmap(pix);
    QString text = QString("red: %1, green: %2, blue: %3, 透明度: %4")
            .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
    ui->colorlabel->setText(text);
}

#define MULTITEXT
void MainWindow::on_inputdlg_clicked()
{
#ifdef INT
    // 父对象，标题，提示信息，默认数据（不指定则为0），最小数据，最大数据，调节步长
    // 返回输入的值
    int ret = QInputDialog::getInt(this, "年龄", "您的年龄：", 10, 1, 100, 2);
    QMessageBox::information(this, "年龄", "您的年龄：" + QString::number(ret));
#endif

#ifdef DOUBLE
    // 最后一位是浮点数精度，2表示小数点后2位
    // 返回输入的值
    double ret = QInputDialog::getDouble(this, "工资", "您的工资：", 2000, 1000, 6000, 2);
    QMessageBox::information(this, "工资", "您的工资：" + QString::number(ret));
#endif
// 下拉菜单
#ifdef ITEM
    QStringList items;
    items << "苹果" << "橙子" << "橘子" << "葡萄" << "香蕉" << "哈密瓜"; // 下拉菜单列表项（<<相当于push_back）
    // 父对象，标题，提示信息，下拉菜单列表
    // 返回选择的项
    QString item = QInputDialog::getItem(this, "请选择你喜欢的水果", "你最喜欢的水果：", items);
    QMessageBox::information(this, "水果", "您最喜欢的水果是：" + item);
#endif

// 单行信息
#ifdef TEXT
    // 父对象，标题，提示信息，显示模式，默认值（可用来记住密码）
    // 返回输入的单行信息
    QString text = QInputDialog::getText(this, "密码", "请输入新的密码：", QLineEdit::Password, "helloworld");
    QMessageBox::information(this, "密码", "您输入的密码是：" + text);
#endif

// 多行信息
#ifdef MULTITEXT
    // 父对象，标题，提示信息，默认值
    QString info = QInputDialog::getMultiLineText(this, "表白", "您最相对漂亮小姐姐说什么呢？", "你好！");
    QMessageBox::information(this, "知心姐姐", "您最想对小姐姐说：" + info);
#endif

}

void MainWindow::on_progressdlg_clicked()
{
    // 1.创建进度条对话框窗口对象
    // 提示信息，取消按钮信息，最小值，最大值，父对象
    QProgressDialog * progress = new QProgressDialog(
                "正在拷贝数据...", "取消拷贝", 0, 100, this);
    // 2.初始化并显示进度条窗口
    // 设置窗口标题并显示（继承自QWidget）
    progress->setWindowTitle("请稍后");
    // 显示窗口前设置为模态窗口，阻塞父窗口
    progress->setWindowModality(Qt::WindowModal);
    progress->show();
    // 3.更新进度条
    // 用定时器，每隔一段时间更新一次进度条
    QTimer *timer = new QTimer(this);
    // 每触发一次定时器就加1
    // 要设置成静态变量，避免槽函数执行完毕后被释放，定时器内部处理错误
    // 这里只是设置了定时器，并没有执行定时，槽函数在接收到信号后只进行了初始化工作
    // 由系统进行定时，因此在槽函数执行完毕后定时还会继续
    static int value = 0;
    connect(timer, &QTimer::timeout, this, [=] ()
    {
        progress->setValue(value);
        value++;
        // 当value > 最大值时（窗口默认自动关闭）
        if (value > progress->maximum())
        {
            timer->stop();
            value = 0;
            delete progress;
            delete timer;
        }
    });

    // 取消按钮按下，关闭窗口
    // 但窗口不会被析构，qt回收机制，要等到父对象析构时，子对象才析构
    // 如果想手动delete释放，可以不赋值父对象，也就是删掉this（也可以不删除）
    connect(progress, &QProgressDialog::canceled, this, [=] ()
    {
        timer->stop();
        value = 0;
        delete progress;
        delete timer;
    });
    // 50ms触发一次
    timer->start(50);
}
