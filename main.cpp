#include <graphics.h>
#include <iostream>
#include "player.cpp"

using namespace std;

	const int screenWidth = 800;
    const int screenHeight = 640;

void drawTutorial() {
    string tutorialText[] = {
        "Welcome to Tiny Spirit!",
        "1. Press arrow keys to move around!",
        "2. Press space bar or up arrow to jump!",
        "3. Avoid enemies on the map!",
        "4. Collect heart collectibles if you lose health!",
        "5. Go to the end point to advance to the next level.",
        "Press SPACE to continue"
    };

    settextstyle(BOLD_FONT, HORIZ_DIR, 5);

    int y = (screenHeight - textheight((char*)tutorialText[0].c_str())) / 3;

    int textWidth = textwidth((char*)tutorialText[0].c_str());
    int x = (screenWidth - textWidth) / 2;
    outtextxy(x, y, (char*)tutorialText[0].c_str());

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    y += textheight((char*)tutorialText[0].c_str()) + 50;

    for (int i = 1; i < 7; i++) {
        textWidth = textwidth((char*)tutorialText[i].c_str());
        x = (screenWidth - textWidth) / 2;
        outtextxy(x, y, (char*)tutorialText[i].c_str());
        y += 30;
    }
}

int main()
{
    initwindow(screenWidth, screenHeight, "Tiny Spirit");
    while (GetAsyncKeyState(VK_SPACE) == 0) {
        drawTutorial();
    }

	char* background = new char[imagesize(0, 0, screenWidth, screenHeight)];
	readimagefile("Assets/Map/bg_new.gif", 0, 0, screenWidth, screenHeight);
	getimage(0, 0, screenWidth, screenHeight, background);

    int page = 0;
    Player player(1);
    while(true)
    {
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        
        putimage(0, 0, background, COPY_PUT);
        player.placeTiles();
        player.placeEnemies();

        player.playerActions(player.posX(), player.posY());
        player.playerJump();
        
        page = 1 - page;
        delay(5);
    }
    return 0;
}