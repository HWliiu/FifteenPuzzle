#include "game.h"
#include "QDebug"
void Game::init()
{
    blocks.clear();//初始化
    for (int i = 0; i < SIZE; i++)
    {
        blocks.push_back(i+1);
    }
    blocks[15] = -1;

    for(int i=0;i<1000;i++)
        scrambles(blocks);
    //std::random_shuffle(blocks.begin(),blocks.end());//STL中一个随机函数,用于打乱数组
    //不能直接用随机数打乱，会造成无解的情况
    moveSound=new QSound("./res/move.wav");
}

void Game::scrambles(std::vector<int> &blocks)//3个一组交换，不会造成无解的情况
{
    std::random_shuffle(a,a+15);
    int temp=blocks[a[0]];
    blocks[a[0]]=blocks[a[1]];
    blocks[a[1]]=blocks[a[2]];
    blocks[a[2]]=temp;

//            qDebug()<<blocks[a[0]];
//            qDebug()<<blocks[a[1]];
//            qDebug()<<blocks[a[2]];
}

void Game::swapWithWhite(int row, int col, Direction dir)
{
    int cur = 4*row + col;//记录当前位置
    int toSwap;//记录要交换的位置
    switch (dir) {
        case rght:
            if (col-1 >= 0) {//边界判断
                toSwap = 4*row + col-1;
                std::swap(blocks[cur],blocks[toSwap]);
                 moveSound->play();
            }
            break;
        case lft:
            if (col+1 <= 3) {
                toSwap = 4*row + col+1;
                std::swap(blocks[cur],blocks[toSwap]);
                 moveSound->play();
            }
            break;
        case down:
            if (row-1 >= 0) {
                toSwap = 4*(row-1) + col;
                std::swap(blocks[cur],blocks[toSwap]);
                 moveSound->play();
            }
            break;
        case up:
            if (row+1 <= 3) {
                toSwap = 4*(row+1) + col;
                std::swap(blocks[cur],blocks[toSwap]);
                 moveSound->play();
            }
            break;
        default:
            break;
    }
}

void Game::swap(Direction dir)
{
    std::vector<int>::iterator it = std::find(blocks.begin(),blocks.end(),-1); //找空白块
    int n = it - blocks.begin();
    swapWithWhite(n/4,n%4,dir);
}

bool Game::win()
{
    for (int i = 0; i < SIZE-1; i++)
    {
        if (blocks[i] != i+1) return false;
    }
    return true;
}

Game::Game()
{
    init();
}

Game::~Game()
{

}

