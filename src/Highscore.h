#ifndef highscore_h
#define highscore_h

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <string.h>
#include <vector>


class Highscore
{
    struct Data {                                   // Data struct for scores
        int     score;          // Player Score
        char    name[11];       // Player Name
    };

public:
    std::string             highscorefile;          // HighScore file
    Data                    highscoreArray[6];      //Array with highscores (type Data)
    int                     numOfSavedScores;       // Keeps track of number of valid scores
    char                    newName[11];            // New name passed to highscore
    int                     newScore;               // New score passed to highscore

public:
    Highscore(std::string);
    Highscore& operator<<(char *);
    Highscore& operator<<(int);

    bool checkIfHighScore();
    void saveToFile();

    std::string getHighScore(int);
};

#endif