#include "TXLib.h"

int wallCollision(int catY)
{
    if (catY < 0)
    {
        catY = 0;
    }
    if (catY > 500)
    {
        catY = 500;
    }

    return catY;
}


void moveCat(int* catX, int* catY, int speed)
{
    if (GetAsyncKeyState(VK_RIGHT))
    {
        *catX = *catX + speed;
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        *catX = *catX - speed;
    }
    if (GetAsyncKeyState(VK_UP))
    {
        *catY = *catY - speed;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        *catY = *catY + speed;
    }
}
//Было
int moveX(int catX, int speed)
{
    if (GetAsyncKeyState(VK_RIGHT))
    {
        catX = catX + speed;
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        catX = catX - speed;
    }

    return catX;
}

//Стало
void moveY(int* catY, int speed)
{
    if (GetAsyncKeyState(VK_UP))
    {
        *catY = *catY - speed;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        *catY = *catY + speed;
    }
}

//Было
int moveY(int catY, int speed)
{
    if (GetAsyncKeyState(VK_UP))
    {
        catY = catY - speed;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        catY = catY + speed;
    }

    return catY;
}





void gemCollision(int catX, int catY, int xGem, int yGem, bool* visibleGem)
{
    //Если столкнулись с бриллиантом
    if (catX - 10 < xGem + 75 &&
        catX + 10 > xGem      &&
        catY - 10 < yGem + 60 &&
        catY + 60 > yGem)
    {
        *visibleGem = false;
    }
}
