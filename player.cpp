#include <graphics.h>
#include <iostream>
#include <queue>
#include <math.h>
#include "player.hpp"
using namespace std;

void Player::readPlayerAssets() {
	playerRight = new char[imagesize(0, 0, width, height)];
	readimagefile("Assets/Player/player_right.gif", 0, 0, width, height);
	getimage(0, 0, width, height, playerRight);

	playerLeft = new char[imagesize(0, 0, width, height)];
	readimagefile("Assets/Player/player_left.gif", 0, 0, width, height);
	getimage(0, 0, width, height, playerLeft);

	playerWalkingRight = new char[imagesize(0, 0, width, height)];
	readimagefile("Assets/Player/Walking/player_right_1.gif", 0, 0, width, height);
	getimage(0, 0, width, height, playerWalkingRight);


	playerWalkingLeft = new char[imagesize(0, 0, width, height)];
	readimagefile("Assets/Player/Walking/player_left_1.gif", 0, 0, width, height);
	getimage(0, 0, width, height, playerWalkingLeft);

	playerEmptyHeart = new char[imagesize(0, 0, width, height)];
	readimagefile("Assets/Player/empty_heart.gif", 0, 0, width, height);
	getimage(0, 0, width, height, playerEmptyHeart);

	playerFullHeart = new char[imagesize(0, 0, width, height)];
	readimagefile("Assets/Player/full_heart.gif", 0, 0, width, height);
	getimage(0, 0, width, height, playerFullHeart);
}

void Player::playerActions(int x, int y) {
	if (getLevel() != 0) {
    	if(GetAsyncKeyState(VK_RIGHT))
		{
			putimage(this->x, this->y, playerWalkingRight, COPY_PUT);
			this->x += speed;
			lookingRight = true;
		}
		else if(GetAsyncKeyState(VK_LEFT))
		{
			putimage(this->x, this->y, playerWalkingLeft, COPY_PUT);
			this->x -= speed;
    	    this->lookingRight = false;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			putimage(this->x, this->y, playerWalkingLeft, COPY_PUT);
			this->y += 1;
		}
		else {
    		if (lookingRight == true)
    		{
				putimage(this->posX(), this->posY(), playerRight, COPY_PUT);
    		}
    		else
    		{
				putimage(this->posX(), this->posY(), playerLeft, COPY_PUT);
    		}
		}
		setPosY(y + 1);
	} else {
		gameOverScreen();
	}

	registerTouchCount();

	if(this->enemyTouchCount == 17) {
		this->enemyTouchCount = 0;
		playerTakeHealth(1);
	}
	
	playerCollision();
	setUI();
	debugMode();

	if (this->debug == true)
	{
		// debug options (will be removed later)
		if(ismouseclick(WM_LBUTTONDOWN)) {
			setPosX(mousex());
			setPosY(mousey() - 32);
			clearmouseclick(WM_LBUTTONDOWN);
		}

		// load main menu
		if (GetAsyncKeyState(0x31)) {
			changeLevel(0);
		}

		// load level 1
		if(GetAsyncKeyState(0x32)) {
			changeLevel(1);
		}
		
		// load level 2
		if(GetAsyncKeyState(0x33)) {
			changeLevel(2);
		}

		// show player X and Y position
		if (GetAsyncKeyState(VK_LSHIFT)) {
			cout << "Player X: " << this->x << endl;
			cout << "Player Y: " << this->y << endl;
		}
	}


	if (getHealth() <= 0) {
		changeLevel(0);
	}
}

void Player::playerJump() {
	if((GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_UP)) && (isJumping != true))
	{
		isJumping = true;
	}

	if (isJumping == true && isOnGround == true)
	{
		isOnGround = false;
		setPosY(y - 56);
	}
}

void Player::playerCollision() {
	// player bounding
	int playerLeft = this->x;
	int playerRight = this->x + width;
	int playerTop = this->y;
	int playerBottom = this->y + height;

	// player cannot go out of bounds
	if (posX() < 0) {
		setPosX(0);
	}
	else if (posX() > (800 - width)) {
		setPosX(768);
	}
	else if (posY() > (600)) {
		playerTakeHealth(this->health);
	}

	for (int i = 0; i < getMapSize(); i++) {
		// tile bounding
		int tileLeft = getMap()[i][0];
		int tileRight = getMap()[i][0] + width;
		int tileTop = getMap()[i][1];
		int tileBottom = getMap()[i][1] + height;
		int tileType = getMap()[i][2];

		if (tileType == 1 || tileType == 2) {
			// check if player is colliding with tile
			if ((playerRight >= tileLeft) && (playerLeft <= tileRight) && (playerBottom >= tileTop) && (playerTop <= tileBottom)) {
				// check if player is colliding with tile from the top
				if (playerBottom - 1 <= tileTop) {
					setPosY(tileTop - height);
					isOnGround = true;
					isJumping = false;
				}
				// check if player is colliding with tile from the bottom
				else if (playerTop + 1 >= tileBottom) {
					setPosY(tileBottom);
					isOnGround = false;
					isJumping = true;
				}
				// check if player is colliding with tile from the left
				else if ((playerRight - 1 >= tileLeft) && lookingRight == false) {
					setPosX(tileLeft + width);
				}
				// check if player is colliding with tile from the right
				else if ((playerLeft + 1 <= tileRight) && lookingRight == true) {
					setPosX(tileRight - (width * 2));
				}
			}
		} else if (tileType == 3) {
			// gain health if player colliding with health tile
			if ((playerRight >= tileLeft) && (playerLeft <= tileRight) && (playerBottom >= tileTop) && (playerTop <= tileBottom)) {
				if (getHealth() < getMaxHealth()) {
					playerGetHealth(1);
					getMap()[i][2] = 50;
				}
			}
		} else if (tileType == 6) {
			// player goes to next level
			if ((playerRight >= tileLeft) && (playerLeft <= tileRight) && (playerBottom >= tileTop) && (playerTop <= tileBottom)) {
				changeLevel(getLevel() + 1);
				getMap()[i][2] = 50;
			}
		}
	}
}

void Player::playerGetHealth(int health) {
	if (health > 0 && this->health != this->max_health) {
		this->health += health;
	}
	else {
		this->health = this->max_health;
	}
};

void Player::playerTakeHealth(int health) {
	if (health > 0 && this->health != 0) {
		this->health -= health;
	}		
}

void Player::setUI() {
	if (getLevel() != 0)
	{
		// set healthbar with full hearts and empty hearts
		for (int i = 0; i < this->max_health; i++) {
			if (i < getHealth()) {
				putimage((790 - (30 * this->getMaxHealth())) + (i * 30), 10, playerFullHeart, COPY_PUT);
			} else {
				putimage((790 - (30 * this->getMaxHealth())) + (i * 30), 10, playerEmptyHeart, COPY_PUT);
			}
		}
		// set level text at bottom right of the screen
		outtextxy(790 - textwidth(getLevelText()), 630 - textheight(getLevelText()), getLevelText());
	}
}

bool Player::playerTouchEnemy() {
    for(int i = 0; i < getEnemiesCount(); i++) {
        if(x + 32 >= getEnemies()[i].posX() && x <= getEnemies()[i].posX() + 32 && y + 32 >= getEnemies()[i].posY() && y <= getEnemies()[i].posY() + 32) {
            return true;
        }
    }
    return false;
}

void Player::registerTouchCount() {
	if(playerTouchEnemy() == 1) {
		setTouchCount(1);
	}
	else {
		if (getTouchCount() > 0)
			setTouchCount(-1);
	}
}

void Player::setStartPos() {
	int* startPos = getStartPos();
	setPosX(startPos[0]);
	setPosY(startPos[1]);
}

void Player::debugMode() {
	if(GetAsyncKeyState(VK_CAPITAL) && this->debug == false) {
		this->debug = true;
		cout << "Debug mode: enabled" << endl;
	} else if(GetAsyncKeyState(VK_CAPITAL) && this->debug == true) {
		this->debug = false;
		cout << "Debug mode: disabled" << endl;
	}
}

void Player::changeLevel(int level) {
	setLevel(level);
	playerGetHealth(getMaxHealth());
	setStartPos();
	placeTiles();
}

void Player::gameOverScreen() {
		int i = 0;
		char text[3][20] = {
						"GAME OVER!", 
						"Press R to restart.",
						"Press ESC to exit."};

		int x = (800 - textwidth(text[0])) / 2;
		int y = (640 - textheight(text[0])) / 2;
		outtextxy(x, y + i, text[0]);

		i += 25;

		x = (800 - textwidth(text[1])) / 2;
		y = (640 - textheight(text[1])) / 2;
		outtextxy(x, y + i, text[1]);

		i += 25;

		x = (800 - textwidth(text[2])) / 2;
		y = (640 - textheight(text[2])) / 2;
		outtextxy(x, y + i, text[2]);

		if (GetAsyncKeyState(0x52)) {
			changeLevel(1);
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			exit(0);
		}
}