#include <graphics.h>

class Enemy
{
    private:
        int x;
        int y;
        int width = 32, height = 32;
        int speed = 1;
        int direction = 0;
        int min_x = 0, max_x = 0;
        char* enemyRight;
        char* enemyLeft;
    public:
        int posX() {return x;}
        int posY() {return y;}
        void readEnemyAssets();
        void drawEnemy();
        Enemy() {}
        Enemy(int x, int y, int min_x, int max_x)
        {
            this->x = x;
            this->y = y;
            this->min_x = min_x;
            this->max_x = max_x;
        }
};

void Enemy::readEnemyAssets()
{
    enemyRight = new char[imagesize(0, 0, width, height)];
    readimagefile("Assets/Enemy/monster_1_right.gif", 0, 0, width, height);
    getimage(0, 0, width, height, enemyRight);

    enemyLeft = new char[imagesize(0, 0, width, height)];
    readimagefile("Assets/Enemy/monster_1_left.gif", 0, 0, width, height);
    getimage(0, 0, width, height, enemyLeft);
}

void Enemy::drawEnemy()
{
    if (direction == 0)
    {
        putimage(this->x, this->y, enemyRight, COPY_PUT);
        this->x += speed;
        if (this->x >= max_x)
        {
            direction = 1;
        }
    }
    else
    {
        putimage(this->x, this->y, enemyLeft, COPY_PUT);
        this->x -= speed;
        if (this->x <= min_x)
        {
            direction = 0;
        }
    }
}