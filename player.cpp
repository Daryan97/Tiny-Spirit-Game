#include <graphics.h>
#include <iostream>
#include "player.hpp"
using namespace std;

// read player assets
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
    	if(GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44))
		{
			putimage(this->x, this->y, playerWalkingRight, COPY_PUT);
			this->x += speed;
			lookingRight = true;
		}
		else if(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41))
		{
			putimage(this->x, this->y, playerWalkingLeft, COPY_PUT);
			this->x -= speed;
    	    this->lookingRight = false;
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
		mainScreen(this->isComplete);
	}

	// if player touches enemy, take 1 health
	registerTouchCount();
	if(this->enemyTouchCount == 17) {
		this->enemyTouchCount = 0;
		playerTakeHealth(1);
	}
	
	playerCollision();
	setUI();
	debugMode();


	// debug mode
	if (this->debug == true)
	{
		// Teleport with Left ALT + Left Mouse Click
		if(ismouseclick(WM_LBUTTONDOWN) && GetAsyncKeyState(VK_LMENU)) {
			setPosX(mousex());
			setPosY(mousey() - 32);
			clearmouseclick(WM_LBUTTONDOWN);
		}

		// Change level to main menu level with 1
		if (GetAsyncKeyState(0x31)) {
			changeLevel(0);
		}

		// Change level to level 1 with 2
		if(GetAsyncKeyState(0x32)) {
			changeLevel(1);
		}
		
		// Change level to level 2 with 3
		if(GetAsyncKeyState(0x33)) {
			changeLevel(2);
		}

		// show player X and Y position with Left Shift + P
		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState(0x50)) {
			cout << "Player X: " << this->x << endl;
			cout << "Player Y: " << this->y << endl;
		}
	}

	// player death
	if (getHealth() <= 0) {
		this->isComplete = false;
		changeLevel(0);
	}
}

// player jump function
void Player::playerJump() {
	if((GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_UP) || GetAsyncKeyState(0x57)) && (isJumping != true))
	{
		isJumping = true;
	}

	if (isJumping == true && isOnGround == true)
	{
		isOnGround = false;
		setPosY(y - 56);
	}
}

// player collision system
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
				if (getLevel() < getLevelCount()) {
					changeLevel(getLevel() + 1);
					getMap()[i][2] = 50;
				} else {
					this->isComplete = true;
					changeLevel(0);
				}
			}
		}
	}
}

// gain health to player
void Player::playerGetHealth(int health) {
	if (health > 0 && this->health != this->max_health) {
		this->health += health;
	}
	else {
		this->health = this->max_health;
	}
};

// take health from player
void Player::playerTakeHealth(int health) {
	if (health > 0 && this->health != 0) {
		this->health -= health;
	}		
}

// set player UI
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

// check if player is touching enemy
bool Player::playerTouchEnemy() {
    for(int i = 0; i < getEnemiesCount(); i++) {
        if(x + 32 >= getEnemies()[i].posX() && x <= getEnemies()[i].posX() + 32 && y + 32 >= getEnemies()[i].posY() && y <= getEnemies()[i].posY() + 32) {
            return true;
        }
    }
    return false;
}

// check if player is touching enemy and register touch ticks
void Player::registerTouchCount() {
	if(playerTouchEnemy()) {
		setTouchCount(1);
	}
	else {
		if (getTouchCount() > 0)
			setTouchCount(-1);
	}
}

// set player start position
void Player::setStartPos() {
	int* startPos = getStartPos();
	setPosX(startPos[0]);
	setPosY(startPos[1]);
}

// enable debu mode with Left CTRL + Left SHIFT + Z
void Player::debugMode() {
	if((GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x5A)) && this->debug == false) {
		this->debug = true;
		cout << "Debug mode: enabled" << endl;
	} else if(GetAsyncKeyState(VK_CAPITAL) && this->debug == true) {
		this->debug = false;
		cout << "Debug mode: disabled" << endl;
	}
}

// change level function
void Player::changeLevel(int level) {
	setLevel(level);
	playerGetHealth(getMaxHealth());
	setStartPos();
	placeTiles();
}

// draw main screen texts
void Player::mainScreen(bool success) {
		int i = 0;
		int typeNum = success == true ? 1 : 0;
		char text[4][20] = {
						"GAME OVER!", 
						"YOU DID IT!",
						"Press R to restart.",
						"Press ESC to exit."};

		int x = (800 - textwidth(text[typeNum])) / 2;
		int y = (640 - textheight(text[typeNum])) / 2;
		outtextxy(x, y + i, text[typeNum]);

		i += 25;

		x = (800 - textwidth(text[2])) / 2;
		y = (640 - textheight(text[2])) / 2;
		outtextxy(x, y + i, text[2]);

		i += 25;

		x = (800 - textwidth(text[3])) / 2;
		y = (640 - textheight(text[3])) / 2;
		outtextxy(x, y + i, text[3]);

		if (GetAsyncKeyState(0x52)) {
			changeLevel(1);
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			exit(0);
		}
}