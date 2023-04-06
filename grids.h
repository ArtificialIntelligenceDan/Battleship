/*******************************************************************************
* File: grids.h
* Dependencies:
*
* Purpose: Contains functions and variables used to interact with data grids
* 
* Course: CS125
* Version:	1.0 - 4/3/23 - Aidan Kihm
*           1.1 - 4/6/23 - Aidan Kihm
*
* Resources: 
*
*******************************************************************************/

#define SIZE 10

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

#define CARRIER 1
#define BATTLESHIP 2
#define CRUISER 3
#define SUBMARINE 4
#define DESTROYER 5

#define HORIZONTAL 0
#define VERTICAL 1

#define OPPONENT 0
#define PLAYER 1

int IsOnGrid(int, int); // Checks if ship is already on grid

int PlaceShip(int, int, int, int, int); // Places ship

void DrawShipGrid(int); // Prints all values in ship grid

void DrawHitGrid(int); // Prints all values in hit grid

void RandomPlace(int, int); // Places ship at random

void ClearGrid(int); // Resets entire grid

void RandomPlaceAll(int); // Places all ships at random

int IsInsideGrid(int, int); // Checks if (row,col) is inside 10x10 grid

int Hit(int, int, int); // Hits a space, 0=Miss 1=Hit

int HitRandom(int); // Hits a random, unhit space

int SmartHit(int); 

int IsSunk(int, int); // Checks if ship has been sunk

int AllSunk(int); // Checks if all ships on grid are sunk