#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSound>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QPoint startRelativePos;//记录鼠标位置
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startGame();

private slots:
    void on_startNewButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::MainWindow *ui;
    Game game;
    QLabel *labels[16];//用QLabel来显示数字块
    QSound *winSound;
    void initLabels();
    void updateView();//更新视图
    void keyPressEvent(QKeyEvent *event);//响应键盘事件
    void mousePressEvent(QMouseEvent *event);//解决隐藏标题栏后窗口无法移动问题
    void mouseMoveEvent(QMouseEvent *event);//csdn上找的解决办法
    void mouseReleaseEvent(QMouseEvent *event);
};



#endif // MAINWINDOW_H
