#include "TXLib.h"

int stolknovenieX(int x)
{
    if (x < 0)
    {
        x = 0;
    }

    return x;
}

int moveX(int x)
{
    if (GetAsyncKeyState('D'))
    {
        x = x + 5;
    }
    if (GetAsyncKeyState('A'))
    {
        x = x - 5;
    }
    return x;
}

int main()
{
    txCreateWindow (800, 600);

    //переменные
    int x = 100;
    int y = 300;


    int xDver = 700;
    int yDver = 250;
    HDC dver = txLoadImage ("dver.bmp");
    int hpDver = 3;




    //игра
    while (x < 800)
    {
        //Очистка экрана
        txSetFillColor(TX_BLACK);
        txClear();


        //персонажи
        if (hpDver > 0)
        {
            //txRectangle(xDver,yDver,xDver+30,yDver+100);
            //txTransparentBlt(txDC(),xDver,yDver,60,90,dver,0,0,TX_WHITE);
            //txBitBlt      (txDC(),xDver,yDver,800,600,dver);
            //txTransparentBlt(txDC(),xDver,yDver,60, 90,  dver,0,0,        TX_WHITE);
            Win32::TransparentBlt(txDC(),xDver,yDver,120,180, dver,0,0, 60,90, TX_WHITE);
        }

        //Герой
        txSetFillColor(TX_WHITE);
        txCircle(x,y, 20);


        //игровая логика
        x = stolknovenieX(x);

        //Движение героя
        x = moveX(x);
        if (GetAsyncKeyState('W'))
        {
            y = y - 5;
        }
        if (GetAsyncKeyState('S'))
        {
            y = y + 5;
        }

        //Движение двери
        if (GetAsyncKeyState(VK_UP))
        {
            yDver = yDver - 5;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            yDver = yDver + 5;
        }


        //Столкновение с дверью
        if (x - 10 < xDver + 10)
        if (x + 10 > xDver)
        if (y - 10 < yDver + 100)
        if (y + 10 > yDver)

        {
           x = 0;
        }





        txSleep(5);            //Пауза

    }

    //Удаление картинок
    txDeleteDC (dver);

    return 0;
}

