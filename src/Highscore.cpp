#include "Highscore.h"


// Open highscore file
Highscore::Highscore(std::string filepath)
{
    highscorefile = "../" + filepath + ".dat";
    numOfSavedScores = 0;

    std::fstream file (highscorefile, std::ios::in | std::ios::binary);

    if (file.good()){
        if (file.peek() != std::ifstream::traits_type::eof()){                  // If file isnt empty
            for(int i = 0; i < 6; i++){                                         // Find out how many scores it contains
                if (!file.eof()){
                    file.read ((char*) &highscoreArray[i], sizeof (Data));
                    numOfSavedScores = i;
                }
            }
        }
    }
    else
        throw "ERROR: Couldnt read highscores file";
    file.close();
}


// Overload << operator so it works by receiving HighscoreObject << PlayerName << Player Score
Highscore& Highscore::operator<<(char* var)
{
    strncpy(newName, var, 11);
    return *this;
}

Highscore& Highscore::operator<<(int var)
{
    newScore = var;

    if ( checkIfHighScore() ){
        saveToFile();
    }
    return *this;
}


bool Highscore::checkIfHighScore()
{
    if (newScore > 0){
        if (numOfSavedScores == 0)                              // If list is empty just add the score
        {
            strncpy( highscoreArray[0].name, newName, 11);
            highscoreArray[0].score = newScore;
            numOfSavedScores = 1;
        }
        else if (numOfSavedScores <= 5)                         // If its not than add score to 6th pos 
        {
            strncpy( highscoreArray[numOfSavedScores].name, newName, 11);
            highscoreArray[numOfSavedScores].score = newScore;
            numOfSavedScores += 1;
        }

        for (int i=0; i < numOfSavedScores-1 ; i++)                // Sort array and keep/save only the top 5
        {
            for (int j=0; j < numOfSavedScores-1 ; j++)
            {
                if (highscoreArray[j].score < highscoreArray[j+1].score)
                {
                    Data temp = highscoreArray[j+1];
                    highscoreArray[j+1] = highscoreArray[j];
                    highscoreArray[j] = temp;
                }
            }
        }
    return true;
    }
    return false;
}


// Return Name and Score for easy printing
std::string Highscore::getHighScore(int i)
{
    if(numOfSavedScores>0){
        if (i <= numOfSavedScores-1){
            std::string temp = highscoreArray[i].name;
            temp += " ";
            temp += std::to_string(highscoreArray[i].score);
            return temp;
        }
    }
    return "";
}


// Overwrite file with scores from array
void Highscore::saveToFile()
{
    std::fstream file (highscorefile, std::ios::out | std::ios::binary | std::ios::trunc);

    if (file.good()){
        for(int i = 0; i < numOfSavedScores; i++){
            file.write ((char*) &highscoreArray[i], sizeof (Data));
        }
    }
    else
        throw "ERROR: Couldnt read highscores file";
    file.close();
}
