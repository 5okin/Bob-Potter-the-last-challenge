/*
Nikos Koutsolelos
Project 2021
NmT1l5CUfgs
*/

#include <iostream>
#include <fstream> 
#include <sstream>
#include <sys/ioctl.h>

#include "Engine.h"
#include "Highscore.h"

int main(int argc, char** argv)
{
    // Location of map and scores directories
    std::string mapsDirectory = "../maps/";
    std::string highScoresDirectory = "../Scores/";

    // Get currnet terminal size, might not work on all systems
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    // Resize terminal window
    std::cout << "\e[8;40;160t" << std::endl;
    
    // Small delay is needed to give time for the terminal to resize,
    // should probably be changed to check if size of terminal has changed.
    sleep(1);

    if (argc < 3){
        if (argc < 2){
            std::cout << "\nERROR: Expected map name as first argument. "
                    << "Maps must be placed in maps directory.\n"
                    << "Only there name must be passed as an argument !\n" <<std::endl;
        }
        if (argc < 3){
             std::cout << "\nERROR: Expected highscore file name as second argument. "
                    << "Highscore file must be placed in top directory.\n"
                    << "Only the name must be passed as an argument!\n" <<std::endl;
        }
        exit (1);
    }

    // Get arguments (map and highscore) given at runtime
    std::string mapname(argv[1]);
    std::string highscore(argv[2]);

    // Start a game
    try{
        Engine newGame(mapname, highscore);
        std::cout << "Thanks for playing!!" ;
    }
    catch(const char * msg){
        std::cerr << msg << std::endl;
    }

    // Return terminal window to original size
    std::cout << "\e[8;"<< w.ws_row << ";" << w.ws_col << "t" << std::endl;

    return 0;
}