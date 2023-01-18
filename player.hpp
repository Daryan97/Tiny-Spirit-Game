#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Maps.cpp"

    class Player : public Map
    {
        private:
		    int max_health = 3;
		    int health = 3;
            int x = 0;
            int y = 0;
            double speed = 5;
            bool lookingRight = true;
            bool isJumping = false;
    		bool isOnGround = true;
	    	const unsigned int width = 32, height = 32;
		    char* playerRight;
    		char* playerLeft;
			bool debug = false;
	    	char* playerWalkingRight;
		    char* playerWalkingLeft;
    		char* playerEmptyHeart;
	    	char* playerFullHeart;
			int enemyTouchCount = 0;
			int debugCount = 0;
			bool topCollision = false;
			bool bottomCollision = false;
			bool leftCollision = false;
			bool rightCollision = false;
        public:
            int posX() {return x;}
            int posY() {return y;}
	    	int getHealth() {return health;}
			int getMaxHealth() {return max_health;}
			int getTouchCount() {return enemyTouchCount;}
			void setTouchCount(int count) {this->enemyTouchCount = enemyTouchCount + count;}
		    void setPosX(int x) {this->x = x;}
    		void setPosY(int y) {this->y = y;}
            void playerActions(int x, int y);
		    void readPlayerAssets();
			void debugMode();
    		void playerJump();
	    	void playerGetHealth(int health);
			void playerTakeHealth(int health);
		    void playerCollision();
		    void setUI();
			bool playerTouchEnemy();
			void registerTouchCount();
			void setStartPos();
			void changeLevel(int level);
			void OLDplayerCollision();
    		Player(int level)
	    	{
				readPlayerAssets();
		    	setLevel(level);
				setStartPos();
				readMapAssets();
		    }
    };

#endif