#ifndef GAME_H
#define GAME_H

#include <vector>
#include <algorithm>
#include <QSound>

enum Direction
{
    rght,//用right会冲突
    lft,//用left会冲突
    down,
    up
};

class Game
{

public:
    int SIZE = 16;
    int a[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//用于产生不重复的几个随机数
    QSound *moveSound;
    std::vector<int> blocks;
    Game();
    ~Game();
    void init();
    void scrambles(std::vector<int> &blocks);//打乱函数
    void swap(Direction dir);
    void swapWithWhite(int row, int col,Direction dir);//与空白块交换
    bool win();

};

#endif // GAME_H
