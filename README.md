# Bob Potter, the last challenge.

Bob Potter, the last challenge is a dungeon crawler top down terminal game developed from scratch in C++ only using ncurses.


## Goal
Bob Potter has to go through a series of dark mysterious dungeon collecting all the jewels to reveal the magic parchment, while avoiding the gnomes and trolls that protect them.

<br>

## Features
The game has a number of feautres including:

- Real time gameplay.
- High score tracking.
- Dynamic window resizing.
- Harder gameplay as you progress the levels.
- Create and play your own maps.

<br>

## Screenshots
Welcome Screen             |  Game            |  End screen
:-------------------------:|:-------------------------:|:-------------------------:
![](https://user-images.githubusercontent.com/70406237/155191738-3fcaf59e-37f9-4707-b5c7-ac5c76f4365c.png) | ![](https://user-images.githubusercontent.com/70406237/155191748-0b210bce-7cb2-45d1-ba8c-4db326bde563.png) | ![](https://user-images.githubusercontent.com/70406237/155191750-bf4c8acf-692d-487c-a99a-e709aa455434.png)

<br>
<p align="center">
<img src="https://user-images.githubusercontent.com/70406237/157918082-de8b129c-c2ef-47f2-a8fd-bcf825fce9ff.gif"/>
</p>

<br>

## Installing

### Dependencies
You need [GCC](https://gcc.gnu.org/) and [ncurses](https://invisible-island.net/ncurses/) to make this project.

<br>

### Compiling

In order to compile, you have to run make from the /src directory.
```sh
cd Bob_Potter/src && make
```
<br>

## Running

After compiling run the ```./bobpotter``` file giving the the name of the map you want to play, which should be in the ```/maps``` directory and the name of the highscore ```.bat``` file.

Example:
```sh
./output map1 highscore
```

<br>

## Maps

Any maps you create can be saved without a file extension. They must be added to the ```/maps``` directory, upon launch you have to specify the name of the map you wish to play on.

The maps are created using space (``` ```) as roads and asterisk (```*```) as walls.

```
************************************************************
*           *              *          *     *            * *
****** * ** * ************ * **** *** * ***   *** **     * *
*    * * **                                 *     **       *
*           ****** * ***** * **** *** ***** ***** **     * *
************************************************************
```


## Highscore

The highscores file is a ```.dat``` binary file (dont ask why) it could be empty or full of scores but it must exist on runtime. If it doesnt just create a empty .dat file using: 
```sh
touch highscore.dat
```
