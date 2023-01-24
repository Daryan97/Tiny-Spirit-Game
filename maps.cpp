#include <graphics.h>
#include <iostream>
#include "maps.hpp"

using namespace std;

// read map assets
void Map::readMapAssets() {
    grassTile = new char[imagesize(0, 0, width, height)];
    readimagefile("Assets/Map/grassTile.gif", 0, 0, width, height);
    getimage(0, 0, width, height, grassTile);

    dirtTile = new char[imagesize(0, 0, width, height)];
    readimagefile("Assets/Map/dirtTile.gif", 0, 0, width, height);
    getimage(0, 0, width, height, dirtTile);

    heartCollectible = new char[imagesize(0, 0, width, height)];
    readimagefile("Assets/Map/Collectibles/heart.gif", 0, 0, width, height);
    getimage(0, 0, width, height, heartCollectible);

    coinCollectible = new char[imagesize(0, 0, width, height)];
    readimagefile("Assets/Map/Collectibles/coin.gif", 0, 0, width, height);
    getimage(0, 0, width, height, coinCollectible);
}

// set map level with tiles, enemies and player spawn
void Map::setLevel(int level) {
    this->level = level;
    this->map = new int*[getMapSize()];
    this->enemies = new Enemy[getMapSize()];
    this->enemiesCount = 0;
    for(int i = 0; i < getMapSize(); i++)
    {
        int x = (((i % this->tileWidthCount) + 1) * this->width) - this->width;
        int y = (((i / this->tileWidthCount) + 1) * this->height) - this->height;
        int type = this->maps[level][i];
        this->map[i] = new int[3];

        if (type == 1 || type == 2 || type == 3 || type == 6)
        {
            this->map[i][0] = x;
            this->map[i][1] = y;
            this->map[i][2] = type;
        }
        else if (type == 4)
        {
            this->playerSpawn[0] = x;
            this->playerSpawn[1] = y;
        }
        else if(type == 5)
        {
            int enemyMinX = x - 64;
            int enemyMaxX = x + 64;
            this->enemies[this->enemiesCount] = Enemy(x, y, enemyMinX, enemyMaxX);
            this->enemies[this->enemiesCount].readEnemyAssets();
            this->enemiesCount++;
        }
        else {
            this->map[i][0] = x;
            this->map[i][1] = y;
            this->map[i][2] = 0;
        }

    }
}

// draw map tiles
void Map::placeTiles() {
    for(int i = 0; i < getMapSize(); i++) {
        if(map[i][2] == 0) {
            continue;
        } else if(map[i][2] == 1) {
            putimage(map[i][0], map[i][1], grassTile, COPY_PUT);
        } else if(map[i][2] == 2) {
            putimage(map[i][0], map[i][1], dirtTile, COPY_PUT);
        } else if (map[i][2] == 3) {
            putimage(map[i][0], map[i][1], heartCollectible, COPY_PUT);
        } else if (map[i][2] == 6) {
            putimage(map[i][0], map[i][1], coinCollectible, COPY_PUT);
        }
    }
}

// draw enemies
void Map::placeEnemies() {
    for(int i = 0; i < getEnemiesCount(); i++) {
        enemies[i].drawEnemy();
    }
}

// get back map level number text
char* Map::getLevelText() {
    char* levelText = new char[10];
    sprintf(levelText, "Level: %d", this->level);
    return levelText;
}