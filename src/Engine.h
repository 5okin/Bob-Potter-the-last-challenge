#ifndef engine_h
#define engine_h

#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <ncurses.h>
#include <fstream> 
#include <sstream>
#include <unistd.h>
#include <chrono>

#include "Highscore.h"
#include "Potter.h"
#include "Gnome.h"
#include "Troll.h"


class Engine
{
    std::vector<std::vector<char>>      maze;                   // 2D char vector with map
    int                                 mapX;                   // Map column and row length
    int                                 mapY;
    int                                 score;                  // Current game score
    int                                 LastGameStatus;         // exit(0), Win (1), lose(2) 
    bool                                showParch = true;       // parchment state
    bool                                finalState = false;     // Has the game ended
    char                                playerName[11];

public:
    Engine(std::string, std::string);

    void LoadMap(std::string);
    void startGame(float, int);
    
    bool welcomeScreen(Highscore &);
    void getPlayerNameScreen(bool);
    void showLevelTwoScreen();

    bool checkCollision (int, int, int=0, int=0);
    void checkForGems(Moving &);
    bool monsterWasOverGem(Moving &);
    void startupRandomPos(Moving &);
    void startupRandomPos(char, int&, int&);
};

#endif