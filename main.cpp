#include "TXLib.h"
#include "moving.cpp"

struct Cat
{
    int x;
    int y;
    int xOld;
    int yOld;
    int HP;
    int speed;
    int catFrame;
    HDC catLeft;
    HDC catRight;
    HDC catUp;
    HDC catDown;
    HDC cat;
};


struct Stena
{
    int x;
    int y;
};

//    int xStena = 300;
//    int yStena = 200;

struct Bullet
{
    int x;
    int y;
    int speed;
    bool visible;
};

void bulletVragStolkn(Bullet* bullet1, int *xVrag, int yVrag)
{
    if (bullet1->x < *xVrag + 122 &&
        bullet1->x > *xVrag       &&
        bullet1->y < yVrag + 26  &&
        bullet1->y > yVrag       &&
        bullet1->visible)
    {
        bullet1->visible = false;
        *xVrag = *xVrag + 30 * bullet1->speed;
    }
}

//    int xBullet = 0;
//    int yBullet = 0;
//    int speedBullet = 5;
//    bool visibleBullet = false;


struct Gem
{
    int x;
    int y;
    bool visible;
    HDC picture;
};
//int xGem = 600;
//int yGem = 200;
//bool visibleGem = true;
//HDC picGem = txLoadImage("Картинки/Gem.bmp");



void stenaVragStolkn(
    int xStena, int yStena,
    int *xVrag, int *yVrag,
    int xVragOld, int yVragOld)
{
    if (xStena       < *xVrag + 122 &&
        xStena + 300 > *xVrag       &&
        yStena       < *yVrag + 26  &&
        yStena +  20 > *yVrag)
    {
        *xVrag = xVragOld;
        *yVrag = yVragOld;
    }
}





void moveKtoTo(int *catX)
{
    if (GetAsyncKeyState(VK_LEFT))
        *catX = *catX - 5;
    if (GetAsyncKeyState(VK_RIGHT))
        *catX = *catX + 5;
}



void changePic(HDC* cat, HDC catLeft, HDC catRight,
                         HDC catUp, HDC catDown)
{
    if (GetAsyncKeyState(VK_RIGHT))
        *cat = catRight;
    else if (GetAsyncKeyState(VK_LEFT))
        *cat = catLeft;
    else if (GetAsyncKeyState(VK_UP))
        *cat = catUp;
    else if (GetAsyncKeyState(VK_DOWN))
        *cat = catDown;
}

void vragStolkn(int catX, int* catY, int *catHP,
                int xVrag, int yVrag,
                int fonX, int fonY)
{
    if ( catX       < xVrag + fonX + 122 &&
         catX + 100 > xVrag + fonX       &&
        *catY       < yVrag + fonY + 26  &&
        *catY + 100 > yVrag + fonY)
    {
        *catY = yVrag - 260;
        *catHP = *catHP - 1;
    }
}

void enemyChase(int catX, int catY, int *xVrag, int *yVrag, int fonX, int fonY)
{
    if (*xVrag + fonX < catX - 10)
        *xVrag = *xVrag + 3;
    if (*xVrag + fonX > catX + 10)
        *xVrag = *xVrag - 3;
    if (*yVrag + fonY < catY - 10)
        *yVrag = *yVrag + 3;
    if (*yVrag + fonY > catY + 10)
        *yVrag = *yVrag - 3;
}


struct Platform
{
    int x;
    int y;
    int x2;
    int y2;
};

int main()
{
    txCreateWindow (800, 600);


    Platform pl1 = {100, 500, 200, 520};
    Platform pl2 = {300, 400, 400, 420};
    Platform pl3 = {500, 500, 600, 520};


    //Переменные
    int fonX = 0;
    int fonY = 0;
    HDC fon = txLoadImage("Картинки/Лабиринт.bmp");

    int xVrag = 250;    int yVrag = 500;
    int xVragOld = 0; int yVragOld = 0;
    HDC picVrag = txLoadImage ("Картинки/Platform.bmp");



    int xVrag2 = 650;    int yVrag2 = 500;


    HDC picGem = txLoadImage("Картинки/Gem.bmp");

    Gem gem1 = {600, 200, true, picGem};
    Gem gem2 = {400, 400, true, picGem};
    Gem gem3 = {500, 400, true, picGem};
    Gem gem4 = {900, 200, true, picGem};


    int xSpeedZone = 300;   int ySpeedZone = 100;

    //Главный герой
    int catX = 50;  int catY = 300;
    int catXOld = 0, catYOld = 0;
    int catHP = 5;  int speed = 10;
    int catFrame = 0;
    HDC catLeft = txLoadImage("Картинки/CatLeft.bmp");
    HDC catRight = txLoadImage("Картинки/CatRight.bmp");
    HDC catUp = txLoadImage("Картинки/CatUp.bmp");
    HDC catDown = txLoadImage("Картинки/CatDown.bmp");
    HDC cat = catLeft;

    int xStena = 300;
    int yStena = 200;
    Stena stena1 = {300, 200};

    Bullet bullet1 = {0, 0, 5, false};

    //Игра
    const char* page = "Игра";
    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        //Очистка экрана
        txSetFillColor(TX_BLACK);
        txClear();

        if (page == "Меню")
        {
            txTextOut(300, 0, "Пауза");

            int sobranoGem = 0;
            if (gem1.visible == false)
            {
                sobranoGem = sobranoGem + 1;
            }
            if (!gem2.visible) sobranoGem++;
            if (!gem3.visible) sobranoGem++;
            if (!gem4.visible) sobranoGem++;

            txTextOut(0, 100, "Бриллианты");
            txSetFillColor(TX_WHITE);
            txRectangle(350, 100, 350 + 50 * 4,             150);
            txSetFillColor(TX_RED);
            txRectangle(350, 100, 350 + 50 * sobranoGem,    150);

            txTextOut(0, 200, "Здоровье");
            txSetFillColor(TX_WHITE);
            txRectangle(350, 200, 350 + 50 * 5,     250);
            txSetFillColor(TX_RED);
            txRectangle(350, 200, 350 + 50 * catHP, 250);

            txRectangle(610, 200, 660, 250);
            txDrawText (610, 200, 660, 250, "+");
            if (sobranoGem == 4 &&
                txMouseButtons() == 1 &&
                txMouseX() >= 610 &&
                txMouseX() <= 660 &&
                txMouseY() >= 200 &&
                txMouseY() <= 250)
            {
                catHP = catHP + 1;
                gem1.visible = true;
                gem2.visible = true;
                gem3.visible = true;
                gem4.visible = true;
            }


            if (txMouseButtons() == 1 &&
                txMouseX() > 700)
            {
                page = "Игра";
            }
        }
        if (page == "Игра")
        {
            if (GetAsyncKeyState('P'))
            {
                page = "Меню";
            }

            catXOld = catX;
            catYOld = catY;

            xVragOld = xVrag;
            yVragOld = yVrag;

            txBitBlt(txDC(), fonX, fonY, 8000, 6000, fon);

            txRectangle(pl1.x + fonX, pl1.y + fonY, pl1.x2 + fonX, pl1.y2 + fonY);
            txRectangle(pl2.x + fonX, pl2.y + fonY, pl2.x2 + fonX, pl2.y2 + fonY);
            txRectangle(pl3.x + fonX, pl3.y + fonY, pl3.x2 + fonX, pl3.y2 + fonY);

            for (int nomer = 0; nomer < catHP; nomer = nomer + 1)
            {
                txCircle(100 + 50 * nomer, 100, 25);
            }

            txRectangle(xStena + fonX, yStena + fonY, xStena + fonX + 300, yStena + fonY + 20);
            /*
            Полет пули
            1) Переменные
            2) Рисуем пулю
            3) Она летит
            4) Она наносит повреждения
            5) Баги
            */

            if (bullet1.visible)
                txCircle(bullet1.x + fonX, bullet1.y + fonY, 5);

            //Выстрел
            if (GetAsyncKeyState(VK_SPACE) &&
                !bullet1.visible)
            {
                bullet1.visible = true;
                bullet1.x = catX - fonX + 30;
                bullet1.y = catY - fonY + 20;
                if (cat == catLeft)
                    bullet1.speed = -5;
                if (cat == catRight)
                    bullet1.speed = 5;
            }

            //Попадание
            if (bullet1.x + fonX < 0)
                bullet1.visible = false;
            if (bullet1.x + fonX > 1000)
                bullet1.visible = false;

            if (bullet1.x < xVrag + 122 &&
                bullet1.x > xVrag       &&
                bullet1.y < yVrag + 26  &&
                bullet1.y > yVrag       &&
                bullet1.visible)
            {
                bullet1.visible = false;
                xVrag = xVrag + 30 * bullet1.speed;
            }

            if (bullet1.visible)
            {
                bullet1.x = bullet1.x + bullet1.speed;
            }


            //Я
            if (catHP > 0)
            {
                txTransparentBlt (txDC(), catX, catY,
                    100, 90, cat, 100 * catFrame, 0, TX_WHITE);

                catFrame = catFrame + 1;
                if (catFrame >= 18)
                    catFrame = 0;
            }


            if (gem1.visible)
                txTransparentBlt(txDC(), gem1.x + fonX, gem1.y + fonY, 75, 60, picGem, 0, 0, TX_BLACK);
            if (gem2.visible)
                txTransparentBlt(txDC(), gem2.x + fonX, gem2.y + fonY, 75, 60, picGem, 0, 0, TX_BLACK);
            if (gem3.visible)
                txTransparentBlt(txDC(), gem3.x + fonX, gem3.y + fonY, 75, 60, picGem, 0, 0, TX_BLACK);
            if (gem4.visible)
                txTransparentBlt(txDC(), gem4.x + fonX, gem4.y + fonY, 75, 60, picGem, 0, 0, TX_BLACK);

            //Враг
            txTransparentBlt (txDC(), xVrag + fonX, yVrag + fonY, 122, 26, picVrag, 0, 0, TX_BLACK);
            txTransparentBlt (txDC(), xVrag2 + fonX, yVrag2 + fonY, 122, 26, picVrag, 0, 0, TX_BLACK);

            //Кнопка
            txRectangle(700, 500, 800, 600);
            txDrawText (700, 500, 800, 600, "Рестарт");

            if (txMouseX() > 700 &&
                txMouseX() < 800 &&
                txMouseY() > 500 &&
                txMouseY() < 600 &&
                txMouseButtons() == 1)
            {
                gem1.visible = true;
                gem2.visible = true;
                gem3.visible = true;
                gem4.visible = true;
            }



            //Игровая логика
            enemyChase(catX, catY, &xVrag, &yVrag, fonX, fonY);


            if (catX < 100)
            {
                catX = catX + 10;
                fonX = fonX + 10;
            }
            if (catX > 700)
            {
                catX = catX - 10;
                fonX = fonX - 10;
            }
            if (catY < 100)
            {
                catY = catY + 10;
                fonY = fonY + 10;
            }
            if (catY > 500)
            {
                catY = catY - 10;
                fonY = fonY - 10;
            }


            //Столкновение с алмазом
            gemCollision(catX, catY, gem1.x + fonX, gem1.y + fonY, &gem1.visible);
            gemCollision(catX, catY, gem2.x + fonX, gem2.y + fonY, &gem2.visible);
            gemCollision(catX, catY, gem3.x + fonX, gem3.y + fonY, &gem3.visible);
            gemCollision(catX, catY, gem4.x + fonX, gem4.y + fonY, &gem4.visible);

            changePic(&cat, catLeft, catRight, catUp, catDown);

            //Столкновение с платформой
            vragStolkn(catX, &catY, &catHP, xVrag, yVrag, fonX, fonY);
            vragStolkn(catX, &catY, &catHP, xVrag2, yVrag2, fonX, fonY);

            //Столкновение со стенами
            catY = wallCollision(catY);

            //Движение
            moveCat(&catX, &catY, speed);

            stenaVragStolkn(xStena, yStena, &xVrag, &yVrag, xVragOld, yVragOld);


            if (xStena + fonX       < catX + 100 &&
                xStena + fonX + 300 > catX       &&
                yStena + fonY       < catY + 90  &&
                yStena + fonY +  20 > catY)
            {
                catX = catXOld;
                catY = catYOld;
            }
        }

        txSleep(30);            //Пауза
    }


    //Все картинки удаляем тут
    txDeleteDC (picVrag);
    txDeleteDC (picGem);

    return 0;
}
