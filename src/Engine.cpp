#include "Engine.h"


Engine::Engine(std::string mapFilePath, std::string highscoreFilePath)
{
    score = 0;
    srand (time(NULL));                     // Used for generating random starting positions

    // Load files
    LoadMap(mapFilePath);
    Highscore hiscore(highscoreFilePath);

    /** The game has 2 levels, it works like PacMan, after the first level is dont the player is spawned in the 2nd level
        the monster move quicker so its more difficult
    **/

    // First parameter is how long until monsters play again
    // Second is the level (only 2 are supported for now)
    if (welcomeScreen(hiscore))
    {
        startGame(0.5 , 1);

        // How state the last game ended in quiet(0), win(1), defeated(2)
        if (LastGameStatus == 1){               // Last game was won so go to level 2
            LoadMap(mapFilePath);
            showLevelTwoScreen();
            showParch = true;
            finalState = false;
            startGame(0.2, 2);                  // Start level 2 with monsters moving faster
        }
        if (LastGameStatus){                    // Check status of last game
            if (LastGameStatus == 1)
                getPlayerNameScreen(true);
            else
                getPlayerNameScreen(false);
            hiscore << playerName << score ;
        }
    }
}


void Engine::LoadMap(std::string filepath)
{
    std::string mapfile = "../maps/" + filepath;
    std::ifstream file;

    int number_of_lines = 0;
    int number_of_colums = 0;
    std::string line;

    // Load map
    file.open (mapfile);
    if (file.is_open()){
        while (std::getline(file, line)){               // Find out size of map
            number_of_colums = line.length();
            ++number_of_lines;
        }
        const int finalLines = number_of_lines;
        const int finalColums = number_of_colums;
        char map[number_of_lines][number_of_colums];
        int i=0, j=0;
        file.clear();                                   // Go back to beginning of file
        file.seekg(0);
        while (!file.eof()){                            // Temporary load data to char array
            char next = file.get();
            if (next != '\n'){
                map[i][j++] = next;
            }
            else {
                j=0;
                i++;
            }
        }
        maze.resize(number_of_lines);                   // Create map vector
        for (int i = 0; i < number_of_lines; i++){
            maze.at(i).resize(number_of_colums);
            for (int j = 0; j < number_of_colums; j++){
                maze[i][j] = map[i][j];
            }
        }
        // Set map size
        mapX = maze.size();
        mapY = maze.at(0).size();
    }
    else
        throw "ERROR: Couldnt read map file";
    file.close();
}


void Engine::startGame(float monsterMoveInterval, int level)
{
    int curx, cury;
    int ch;
    initscr ();
    start_color();
    raw();
    noecho();
    curs_set(0);
    refresh ();
    clear ();

    // Setup colors for all entities
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_WHITE);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);

    // Make terminal background color black
    mvchgat(0, 0, -1, A_BLINK, 1, NULL);

    auto start = std::chrono::high_resolution_clock::now();

    //Add Gemstones to map (printed with the map)
    int numOfGems = 10;
    for (int i=0; i < numOfGems; i++){
        int x;
        int y;
        startupRandomPos('J', x, y);
    }

    //Draw map and menu w/ stats and controls around it
    for (int i = 0; i < mapX; i++){
        for (int j = 0; j < mapY; j++){
            mvaddch(i, mapY + 5, '|');
            if (i == 1){
                move(i, mapY + 7);
                printw("Level:");
                move(i, mapY + 14);
                printw("%d", level);
            }
            if (i == 2){
                move(i, mapY + 7);
                printw("Score:");
            }
            if (i == 4){
                move(i, mapY + 7);
                attron(COLOR_PAIR(2));
                printw("B");
                attroff(COLOR_PAIR(2));
                move(i, mapY + 9);
                printw(": Bob Potter");
            }
            if (i == 5){
                move(i, mapY + 7);
                attron(COLOR_PAIR(4));
                printw("J");
                attroff(COLOR_PAIR(4));
                move(i, mapY + 9);
                printw(": Jewels");
            }
            if (i == 6){
                move(i, mapY + 7);
                attron(COLOR_PAIR(6));
                printw("P");
                attroff(COLOR_PAIR(6));
                move(i, mapY + 9);
                printw(": Magic Parchment");
            }
            if (i == 7){
                move(i, mapY + 7);
                attron(COLOR_PAIR(3));
                printw("G");
                attroff(COLOR_PAIR(3));
                move(i, mapY + 9);
                printw(": Gnome");
            }
            if (i == 8){
                move(i, mapY + 7);
                attron(COLOR_PAIR(3));
                printw("T");
                attroff(COLOR_PAIR(3));
                move(i, mapY + 9);
                printw(": Troll");
            }
            if (i == 10){
                move(i, mapY + 7);
                attron(A_BOLD);
                printw("ESC");
                attroff(A_BOLD);
                move(i, mapY + 11);
                printw(": to exit game");
            }
            if (i == 10){
                move(i, mapY + 7);
                printw("Use arrow keys to play");
            }
            if (maze[i][j] == '*'){
                attron(COLOR_PAIR(5));
                mvaddch(i, j, maze[i][j]);
                attroff(COLOR_PAIR(5));
            }
            else if (maze[i][j] == 'J'){
                attron(COLOR_PAIR(4));
                mvaddch(i, j, maze[i][j]);
                attroff(COLOR_PAIR(4));
            }
            else
                mvaddch(i, j, maze[i][j]);
        }
    }

    // Create characters and add them to random location
    Potter potter;
    startupRandomPos (potter);
    attron(COLOR_PAIR(2));
    mvaddch(potter.currY(), potter.currX(), potter.style());
    attroff(COLOR_PAIR(2));

    Gnome gnome;
    startupRandomPos (gnome);
    attron(COLOR_PAIR(3));
    mvaddch(gnome.currY(), gnome.currX(), gnome.style());
    attroff(COLOR_PAIR(3));

    Troll Troll;
    startupRandomPos (Troll);
    attron(COLOR_PAIR(3));
    mvaddch(Troll.currY(), Troll.currX(), Troll.style());
    attroff(COLOR_PAIR(3));

    nodelay(stdscr, TRUE);
    keypad (stdscr,TRUE);

    do{
        //keypad (stdscr,TRUE);
        //keypad (stdscr,FALSE);
        ch = getch ();

        move(potter.currY(), potter.currX());
        addch (' ');

        // Get user input switch, check for collision
        switch (ch)
        {
            case KEY_UP:
                if (checkCollision (potter.currY(), potter.currX(), -1, 0))
                {
                    potter.Move(-1, 0);
                    checkForGems(potter);
                }
                break;
            case KEY_DOWN:
                if (checkCollision (potter.currY(), potter.currX(), 1, 0))
                {
                    potter.Move(1, 0);
                    checkForGems(potter);
                }
                break;
            case KEY_LEFT:
                if (checkCollision (potter.currY(), potter.currX(), 0, -1))
                {
                    potter.Move(0, -1);
                    checkForGems(potter);
                }
                break;
            case KEY_RIGHT:
                if (checkCollision (potter.currY(), potter.currX(), 0, 1))
                {
                    potter.Move(0, 1);
                    checkForGems(potter);
                }
                break;
            default:
                break;
        }

        // Update Potter location
        attron(COLOR_PAIR(2));
        mvaddch(potter.currY(), potter.currX(), potter.style());
        attroff(COLOR_PAIR(2));

        // Update on screen score
        move (2, mapY + 14);
        printw("%d", score);

        // Check win state
        if (level == 1){
            if (score == 100 && showParch){                         // If parchment hasnt been spawned, spawn it
                showParch = false;
                // All jewels have been found, show parchment
                int x=0;
                int y=0;
                // Print parchment
                startupRandomPos('P', x, y);
                attron(COLOR_PAIR(6));
                mvaddch(x, y, 'P');
                attroff(COLOR_PAIR(6));
            }
        }
        else if (level == 2){
            if (score == 300 && showParch){                         // If parchment hasnt been spawned, spawn it
                showParch = false;
                // All jewels have been found, show parchment
                int x=0;
                int y=0;
                // Print parchment
                startupRandomPos('P', x, y);
                attron(COLOR_PAIR(6));
                mvaddch(x, y, 'P');
                attroff(COLOR_PAIR(6));
            }
        }

        if (score == (200*level)){                                  // If score=200 game is over
            LastGameStatus = 1;
            finalState = true;
        }

        ///////////////////////////////////////////////// Game Moves /////////////////////////////////////////////////
        // Game speed (Monster Speed), used for greater accuracy compaired to time
        std::chrono::duration<double>  gametime = std::chrono::high_resolution_clock::now() - start;

        // Run monster moves every round.
        if (gametime.count() >= monsterMoveInterval){
            start = std::chrono::high_resolution_clock::now();      // Restart timer

            move(Troll.currY(), Troll.currX());
            addch (' ');

            move(gnome.currY(), gnome.currX());
            addch (' ');

            // Move Gnome
            gnome.findMove(maze, potter.currY(), potter.currX());

            if (checkCollision (gnome.currY(), gnome.currX(), gnome.getNextY(), gnome.getNextX()))
            {
                gnome.Move(gnome.getNextY(), gnome.getNextX());
            }

            // Move Troll
            Troll.findMove(maze, potter.currY(), potter.currX());

            if (checkCollision (Troll.currY(), Troll.currX(), Troll.getNextY(), Troll.getNextX()))
            {
                Troll.Move(Troll.getNextY(), Troll.getNextX());
            }

            // Update Gnome location
            attron(COLOR_PAIR(3));
            mvaddch(gnome.currY(), gnome.currX(), gnome.style());
            attroff(COLOR_PAIR(3));

            // Update Troll location
            attron(COLOR_PAIR(3));
            mvaddch(Troll.currY(), Troll.currX(), Troll.style());
            attroff(COLOR_PAIR(3));
        }

        // Re-Draw jem or parchment if Troll was over it last turn
        if (maze[Troll.getPastY()][Troll.getPastX()] != ' '){
            attron(COLOR_PAIR(4));
            mvaddch(Troll.getPastY(), Troll.getPastX(), maze[Troll.getPastY()][Troll.getPastX()]);
            attroff(COLOR_PAIR(4));
        }

        // Re-Draw jem or parchment if gnome was over it last turn
        if (maze[gnome.getPastY()][gnome.getPastX()] != ' '){
            attron(COLOR_PAIR(4));
            mvaddch(gnome.getPastY(), gnome.getPastX(), maze[gnome.getPastY()][gnome.getPastX()]);
            attroff(COLOR_PAIR(4));
        }

        // Check if potter got eaten
        if (potter.currY() == gnome.currY() && potter.currX() == gnome.currX()){
            LastGameStatus = 2;
            finalState = true;
        }
        else if ((potter.currY() == Troll.currY() && potter.currX() == Troll.currX())){
            LastGameStatus = 2;
            finalState = true;
        }
    }
    while (ch != 27 && finalState==false);

    if (ch == 27)               // Check if game was ended by player (ESC)
        LastGameStatus = 0;     // Just exit the game (Dont show score screen even he has one)

    // Clean up nCurses
    refresh();
    clear();
    keypad (stdscr,FALSE);
    nodelay(stdscr, FALSE);
    echo();
    endwin ();
}


// Checks if next move is possible
bool Engine::checkCollision (int curry, int currx, int goingy, int goingx)
{
    // Wall collisions
    if (maze[curry + goingy][currx + goingx] != '*'){
        return true;
    }
    return false;
}


void Engine::checkForGems(Moving &character){
    // Jewels and perchment collisions
    if (maze[character.currY()][character.currX()] == 'J'){
        maze[character.currY()][character.currX()] = ' ';
        score += 10;
    }
    else if (maze[character.currY()][character.currX()] == 'P'){
        maze[character.currY()][character.currX()] = ' ';
        score += 100;
    }
}


// For character random pos
void Engine::startupRandomPos (Moving &character)
{
    //Select random posistions in map
    while(true){
        int randx = 1 + std::rand() % (mapX) - 1;
        int randy = 1 + std::rand() % (mapY) - 1;

        // Check if possistion is free
        if (maze[randx][randy] == ' '){
            character.setCoordinates(randx, randy);
            break;
        }
    }
}

// For adding Gemstones and parchment to map
void Engine::startupRandomPos (char c, int &x, int &y)
{

    while(true){
        int randx = 1 + std::rand() % (mapX) - 1;
        int randy = 1 + std::rand() % (mapY) - 1;

        // Check if possistion is free
        if (maze[randx][randy] == ' '){
            x = randx;
            y = randy;
            maze[randx][randy] = c;
            break;
        }
    }
}


void Engine::showLevelTwoScreen(){                                              // Screen shown between level 1 and level 2
    initscr();                                                                  // Notifying player he is moving on and showing his score
    curs_set(0);
    refresh ();
    clear ();
    noecho();
    int ch;
    int row,col;
    getmaxyx(stdscr,row,col);
    char status[20] = "You Won level 1 !!!";
    char txt[22] = "Your score so far is:";
    char prsenter[46] = "Press Enter when youre ready to start level 2";
    mvprintw(2, (col-strlen(status))/2,"%s",status);
    mvprintw(4, (col-strlen(txt))/2,"%s %d",txt, score);
    mvprintw(6, (col-strlen(prsenter))/2,"%s",prsenter);

    // Wait for user to press enter
    do{
        ch = getch ();
    }while (ch != '\n');
}


bool Engine::welcomeScreen(Highscore &hi){                                          // Screen with game title and highscores
    initscr();
    start_color();
    nodelay(stdscr, TRUE);
    keypad (stdscr,TRUE);
    int row,col;
    int ch;
    noecho();
    curs_set(0);
    refresh ();

    mvchgat(0, 0, -1, A_BLINK, 1, NULL);
    getmaxyx(stdscr,row,col);

    char title[] = "Bob Potter";
    mvprintw(2, (col-strlen(title))/2,"%s",title);

    char game[] = "T H E    L A S T    C H A L L E N G E";
    mvprintw(4, (col-strlen(game))/2,"%s",game);

    char con[] = "< Press Enter to start playing >";
    mvprintw(LINES-4, (col-strlen(con))/2,"%s",con);

    char ext[] = "< ESC to exit >";
    mvprintw(LINES-3, (col-strlen(ext))/2,"%s",ext);

    char highscore[] = "--HIGHSCORES--";
    mvprintw(10, (col-strlen(highscore))/2,"%s",highscore);

    for (int i=0; i < 5; i++){
        move (12+i, (col-hi.getHighScore(i).length())/2);
        printw(hi.getHighScore(i).data());
    }

    do{
        ch = getch ();
        if (ch == 27){
            endwin ();
            return false;
        }
        else if (ch == '\n')
        {
            return true;
        }
    }while (true);
}


void Engine::getPlayerNameScreen(bool won)
{
    initscr();
    char name[11];
    curs_set(0);                                                 // Show cursor for user to enter text
do {
        refresh ();
        clear ();
        int row,col;                                            // Store the number of rows & colums of the screen
        getmaxyx(stdscr,row,col);
        name[0] = '\0';                                         // Zero out name char

        // Show Win or Lose message and player score
        if (won){
            char status[] = "!! You Won !!";
            mvprintw(2, (col-strlen(status))/2,"%s",status);
        }
        else{
            char status[] = "-You Lost-";
            mvprintw(2, (col-strlen(status))/2,"%s",status);
        }

        char scorestring[] = "Your score was: ";
        mvprintw(row/4, (col-strlen(scorestring))/2,"%s%d",scorestring, score);

        if (score > 0){                                                                 // If player got a score ask for name
            curs_set(2);
            char warn[]="Enter your name (up to 10 letters) and hit Enter";

            char mesg[]="Enter a your name: ";
            mvprintw(row/2+1,(col-strlen(warn))/2,"%s",warn);
            mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);

            getstr(name);

            // Check if name is less than 10 char long and notify user
            if (strlen(name) > 10){
                mvprintw((row/2)+3,(col-20)/2,"To many characters !");
                mvprintw((row/2)+4,(col-20)/2,"Press enter and try again");
                getch();
            }
            else if (strlen(name) == 0){
                mvprintw((row/2)+3,(col-20)/2, "Please give a name");
                mvprintw((row/2)+4,(col-20)/2,"Press enter and try again");
                getch();
            }
        }
        else{                                                                           // Else just notify him he lost and exit
            int ch;
            noecho();
            char mesg[]="Press enter to exit";
            mvprintw((row/4)+1, (col-strlen(mesg))/2,"%s",mesg);
            do{
                ch = getch();
            }while (ch != '\n');
            break;
        }
    }
    while ( (strlen(name) ==  0) || (strlen(name) > 10) );
    strncpy(playerName, name, 11);
    endwin();
}
