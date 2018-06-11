#include "game.h"

void Field::init()
{
    blocks.clear();//初始化
    for (int i = 0; i < SIZE; i++)
    {
        blocks.push_back(i+1);
    }
    blocks[15] = -1;
    std::random_shuffle(blocks.begin(),blocks.end());//STL中一个随机函数,用于打乱数组
}

void Field::swapWithWhite(int row, int col, Direction dir)
{
    int cur = 4*row + col;
    int toSwap;
    switch (dir) {
        case rght:
            if (col-1 >= 0) {
                toSwap = 4*row + col-1;
                std::swap(blocks[cur],blocks[toSwap]);
            }
            break;
        case lft:
            if (col+1 <= 3) {
                toSwap = 4*row + col+1;
                std::swap(blocks[cur],blocks[toSwap]);
            }
            break;
        case down:
            if (row-1 >= 0) {
                toSwap = 4*(row-1) + col;
                std::swap(blocks[cur],blocks[toSwap]);
            }
            break;
        case up:
            if (row+1 <= 3) {
                toSwap = 4*(row+1) + col;
                std::swap(blocks[cur],blocks[toSwap]);
            }
            break;
        default:
            break;
    }
}

void Field::swap(Direction dir)
{
    std::vector<int>::iterator it = std::find(blocks.begin(),blocks.end(),-1); //找空白块
    int n = it - blocks.begin();
    swapWithWhite(n/4,n%4,dir);
}

bool Field::win()
{
    for (int i = 0; i < SIZE-1; i++)
    {
        if (blocks[i] != i+1) return false;
    }
    return true;
}

Field::Field()
{
    init();
}

Field::~Field()
{

}

