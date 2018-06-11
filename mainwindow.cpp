#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    winSound=new QSound("./res/win.wav");
    initLabels();
    updateView();
    ui->startNewButton->setAutoFillBackground(true);
    ui->closeButton->setAutoFillBackground(true);
    ui->startNewButton->setFlat(true);
    ui->closeButton->setFlat(true);
    for (int i = 0; i < game.SIZE; i++)
    {
        int row = i / 4;
        int col = i % 4;
        ui->grid->addWidget(labels[i],row,col);//将lables加入网格布局
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    QFont font;
    font.setPixelSize(20);
    font.setFamily("隶书");
    ui->label->setFont(font);
    ui->label->setAlignment(Qt::AlignCenter);
    game.init();
    ui->label->setText("用 W S A D 移 动 方 块");
}

void MainWindow::updateView()
{
    std::vector<int> nums = game.blocks;
    for (int i = 0; i < game.SIZE; i++)
    {
        labels[i]->setText(QString::number(nums[i]));//将Game类中的blocks的值在lables中显示出来
        labels[i]->setStyleSheet("QLabel { background-color: GreenYellow; }");
        if (nums[i] == -1)
        {
            labels[i]->setStyleSheet("QLabel { background-color: rgba(1,1,1,0); }");//css样式,设置空白块
            labels[i]->setText("");
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if(game.win())//胜利后不需要响应键盘事件
        return;

    QFont font;
    font.setPixelSize(20);
    font.setFamily("隶书");
    ui->label->setFont(font);
    ui->label->setAlignment(Qt::AlignCenter);


    switch (event->key()) {
    case Qt::Key_A:
        game.swap(lft);
        break;
    case Qt::Key_D:
        game.swap(rght);
        break;
    case Qt::Key_W:
        game.swap(up);
        break;
    case Qt::Key_S:
        game.swap(down);
        break;
    default:
        break;
    }

    updateView();
    if (game.win())
    {
        ui->label->setText("恭 喜 你 通 关!");
        winSound->play();
        return;
    }

}

void MainWindow::on_startNewButton_clicked()
{
    startGame();
    updateView();
}

void MainWindow::on_closeButton_clicked()
{
    window()->close();
}

void MainWindow::initLabels()
{
    QFont font;
    font.setBold(true);
    font.setPixelSize(20);
    font.setFamily("jokerman");
    for (int i = 0; i < game.SIZE; i++)
    {
        labels[i] = new QLabel(" ");
        labels[i]->setFont(font);
        labels[i]->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){//这几行代码是从CSDN上找的
    if(event->buttons() == Qt::LeftButton)//有个不足之处是鼠标放在开始游戏按钮上拖动窗口时，窗口会抖一下
        startRelativePos=event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton)
        move(event->globalPos()-startRelativePos);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    event->accept();
}
