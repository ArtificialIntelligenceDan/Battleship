#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

// Grid Variables
const int OPPONENT = 0;
const int PLAYER = 1;

int shipGrid[SIZE][SIZE][2];
int hitGrid[SIZE][SIZE][2];
//          COLS  ROWS  ^ 0=Opponent 1=Player

// Ship Variables
const int CARRIER = 1;
const int BATTLESHIP = 2;
const int CRUISER = 3;
const int SUBMARINE = 4;
const int DESTROYER = 5;

const int LENGTH[6] = {0, 5,4,3,3,2};
//         placeholder ^

// Orientation Variables
const int HORIZONTAL = 0;
const int VERTICAL = 1;

// Display Variables
char gridUnit[3][5] = {"+---+",
                       "|   |",
                       "+---+"};
char missIcon = '.';
char hitIcon = 'X';
char blankIcon = ' ';
char shipIcon = 'O';

char displayGrid[21][41][2];


int IsOnGrid(int ship, int grid){ // Check if ship is already on grid
    int isOnGrid = 0;
    int y;
    for (y = 0; y < SIZE; y++){
        int x;
        for (x = 0; x < SIZE; x++){
            if (shipGrid[x][y][grid] == ship){
                isOnGrid = 1;
            }
        }
    }
    return isOnGrid;
}

int PlaceShip(int ship, int grid, int orient, int row, int col){ // Place ship
    int canPlace = 0;
    
    if (IsOnGrid(ship,grid) == 0){ // If ship isn't already on grid
        if (orient == HORIZONTAL){
            int x;
            for (x = col; x < col+LENGTH[ship]; x++){
                if (x >= SIZE || shipGrid[x][row][grid] != 0){
                    canPlace = 0;
                    break;
                }
                canPlace = 1;
            }
            
            if (canPlace){
                for (x = col; x < col+LENGTH[ship]; x++){
                    shipGrid[x][row][grid] = ship;
                }
            }
        }
        else if (orient == VERTICAL){
            int y;
            
            // Check if can place
            for (y = row; y < row+LENGTH[ship]; y++){
                if (y >= SIZE || shipGrid[col][y][grid] != 0){
                    canPlace = 0;
                    break;
                }
                canPlace = 1;
            }
            
            if (canPlace){
                for (y = row; y < row+LENGTH[ship]; y++){
                    shipGrid[col][y][grid] = ship; // Insert ship in slots
                }
            }
        }
    }
    
    return canPlace;
}

void DrawGrid(int grid){ // Print all values in ship grid
    int y;
    for (y = 0; y < SIZE; y++){
        int x;
        for (x = 0; x < SIZE; x++){
            printf("%d ", shipGrid[x][y][grid]);
        }
        printf("\n");
    }

}

void DrawHitGrid(int grid){ // Print all values in hit grid
    int y;
    for (y = 0; y < SIZE; y++){
        int x;
        for (x = 0; x < SIZE; x++){
            printf("%d ", hitGrid[x][y][grid]);
        }
        printf("\n");
    }

}

void RandomPlace(int ship, int grid){ // Place ship at random
    int x, y;
    x = rand()%(SIZE-LENGTH[ship])+0;
    y = rand()%(SIZE-LENGTH[ship])+0;
    int orient = rand()%2+0;
    
    int placed = 0;
    int tries = 0;
    while (placed == 0 || tries >= 100){
        x = rand()%(SIZE-LENGTH[ship])+0;
        y = rand()%SIZE+0;
        orient = rand()%2+0;
        placed = PlaceShip(ship, grid, orient, x, y);
        
        tries++;
    }
    
    if (placed == 0 || tries >= 100){
        printf("Could not place ship.");
    }
}

void ClearGrid(int grid){ // Reset entire grid
    int y;
    for (y = 0; y < SIZE; y++){
        int x;
        for (x = 0; x < SIZE; x++){
            shipGrid[x][y][grid] = 0;
        }
    }
}

void RandomPlaceAll(int grid){ // Place all ships at random
    ClearGrid(grid);
    int i;
    for (i = 1; i <= 5; i++){
        RandomPlace(i, grid);
    }
}

int IsInsideGrid(int row, int col){
    int inside = 0;
    if ((row < SIZE && col < SIZE) && (row >= 0 && col >= 0)){
        inside = 1;
    }
    return inside;
}

int Hit(int row, int col, int grid){ // Hit a space, 0=Miss 1=Hit
    if (shipGrid[col][row][grid] != 0){
        hitGrid[col][row][grid] = 1;
        return 1;
    }
    else{
        hitGrid[col][row][grid] = -1;
        return 0;
    }
}

int HitRandom(int grid){ // Hits a random, unhit space
    int row,col;
    do{
        row = rand()%SIZE+0;
        col = rand()%SIZE+0;
    } while(hitGrid[col][row][grid] != 0);
    
    int hit = Hit(row,col,grid);
    
    return hit;
}

int SmartHit(int grid){
    /* Searches for the first hit space that hasn't been sunk and
    an uses a simple algorithm to determine where to hit around that
    space */ 
    
    int row,col,hit,sunk,hitCol,hitRow;
    int targetFound = 0;
    for (row = 0; row < SIZE; row++){
        for (col = 0; col < SIZE; col++){
            hit = hitGrid[col][row][grid];
            sunk = hit ? IsSunk(shipGrid[col][row][grid], grid) : 0;
            if (hit && !sunk){
                targetFound = 1;
                break;
            }
        }
        if (hit == 1 && !sunk){
            break;
        }
    }
    
    hitRow = row;
    hitCol = col;
    
    if (targetFound){
        int dir = -1;
        int attemptedDir = -1;
        
        if (IsInsideGrid(row,col-1) && hitGrid[col-1][row][grid] == 1 && !IsSunk(shipGrid[col-1][row][grid])){
            dir = HORIZONTAL;
        }
        else if (IsInsideGrid(row,col+1) && hitGrid[col+1][row][grid] == 1 && !IsSunk(shipGrid[col+1][row][grid])){
            dir = HORIZONTAL;
        }
        else if (IsInsideGrid(row-1,col) && hitGrid[col][row-1][grid] == 1 && !IsSunk(shipGrid[col][row-1][grid])){
            dir = VERTICAL;
        }
        else if (IsInsideGrid(row+1,col) && hitGrid[col][row+1][grid] == 1 && !IsSunk(shipGrid[col][row+1][grid])){
            dir = VERTICAL;
        }
        
        int resolved = 1;
        do{
            if (dir == HORIZONTAL){
                int shiftDir = rand()%2;
                if (shiftDir == 0){ // Left
                    while(IsInsideGrid(row,col-1) && hitGrid[col][row][grid] == 1){
                        col--;
                    }
                    
                    if (hitGrid[col][row][grid] == 0){
                        hit = Hit(row,col,grid);
                        resolved = 1;
                    }
                    else{
                        do{
                            col++;
                        }while(IsInsideGrid(row,col+1) && hitGrid[col][row][grid] == 1);
                        
                        if (hitGrid[col][row][grid] == 0){
                            hit = Hit(row,col,grid);
                            resolved = 1;
                        }
                        else{
                            attemptedDir = dir;
                            dir = -1; // likely hit two ships, direction not known
                        }
                    }
                }
                else{ // Right
                    while(IsInsideGrid(row,col+1) && hitGrid[col][row][grid] == 1){
                        col++;
                    }
                    
                    if (hitGrid[col][row][grid] == 0){
                        hit = Hit(row,col,grid);
                        resolved = 1;
                    }
                    else{
                        do{
                            col--;
                        }while(IsInsideGrid(row,col-1) && hitGrid[col][row][grid] == 1);
                        
                        if (hitGrid[col][row][grid] == 0){
                            hit = Hit(row,col,grid);
                            resolved = 1;
                        }
                        else{
                            attemptedDir = dir;
                            dir = -1; // likely hit two ships, direction not known
                        }
                    }
                }
            }
            else if (dir == VERTICAL){
                int shiftDir = rand()%2;
                if (shiftDir == 0){ // Up
                    while(IsInsideGrid(row-1,col) && hitGrid[col][row][grid] == 1){
                        row--;
                    }
                    
                    if (hitGrid[col][row][grid] == 0){
                        hit = Hit(row,col,grid);
                        resolved = 1;
                    }
                    else{
                        do{
                            row++;
                        }while(IsInsideGrid(row+1,col) && hitGrid[col][row][grid] == 1);
                        
                        if (hitGrid[col][row][grid] == 0){
                            hit = Hit(row,col,grid);
                            resolved = 1;
                        }
                        else{
                            attemptedDir = dir;
                            dir = -1; // likely hit two ships, direction not known
                        }
                    }
                }
                else{ // Down
                    while(IsInsideGrid(row+1,col) && hitGrid[col][row][grid] == 1){
                        row++;
                    }
                    
                    if (hitGrid[col][row][grid] == 0){
                        hit = Hit(row,col,grid);
                        resolved = 1;
                    }
                    else{
                        do{
                            row--;
                        }while(IsInsideGrid(row-1,col) && hitGrid[col][row][grid] == 1);
                        
                        if (hitGrid[col][row][grid] == 0){
                            hit = Hit(row,col,grid);
                            resolved = 1;
                        }
                        else{
                            attemptedDir = dir;
                            dir = -1; // likely hit two ships, direction not known
                        }
                    }
                }
            }
            
            if (dir == -1){ // If direction not known
                row = hitRow;
                col = hitCol;
            
                if (IsInsideGrid(row,col-1) && hitGrid[col-1][row][grid] == 0){
                    hit = Hit(row,col-1,grid); // hit left
                    resolved = 1;
                }
                else if (IsInsideGrid(row,col+1) && hitGrid[col+1][row][grid] == 0){
                    hit = Hit(row,col+1,grid); // hit right
                    resolved = 1;
                }
                else if (IsInsideGrid(row-1,col) && hitGrid[col][row-1][grid] == 0){
                    hit = Hit(row-1,col,grid); // hit up
                    resolved = 1;
                }
                else if (IsInsideGrid(row+1,col) && hitGrid[col][row+1][grid] == 0){
                    hit = Hit(row+1,col,grid); // hit down
                    resolved = 1;
                }
                else{
                    resolved = 0;
                    dir = !attemptedDir;
                }
            }
        }while(!resolved);
    }
    else{
        hit = HitRandom(grid);
    }
    
    return hit;
}

int IsSunk(int ship, int grid){ // Check if ship has been sunk
    int y;
    int hits = 0;
    
    for (y = 0; y < SIZE; y++){
        int x;
        for (x = 0; x < SIZE; x++){
            if (shipGrid[x][y][grid] == ship && hitGrid[x][y][grid] == 1){
                hits++;
            }
        }
    }
    
    if (hits >= LENGTH[ship]){
        return 1;
    }
    else{
        return 0;
    }
}

int AllSunk(int grid){ // Returns 1 if all ships on grid are sunk
    int sunkAmt = 0;
    int allSunk = 0;
    int ship;
    for (ship = 1; ship <= 5; ship++){
        if (IsSunk(ship, grid)){
            sunkAmt++;
        }
    }
    
    if (sunkAmt >= 5){
        allSunk = 1;
    }
    
    return allSunk;
}

void UpdateDisplayGrid(int grid){ // Update the specified displayGrid array 
    int y;
    for (y = 0; y < 10; y++){
        int x;
        for (x = 0; x < 10; x++){
            int row;
            for (row = 0; row < 3; row++){
                int col;
                for (col = 0; col < 5; col++){
                    if (row == 1 && col == 2){
                        if (grid == PLAYER){
                            if (shipGrid[x][y][grid] != 0){ // If ship
                                displayGrid[2*y + row][4*x + col][grid] = shipIcon;
                            }
                            else if (hitGrid[x][y][grid] == 0){ // If not hit
                                displayGrid[2*y + row][4*x + col][grid] = blankIcon;
                            }
                            else if (hitGrid[x][y][grid] == -1){ // If miss
                                displayGrid[2*y + row][4*x + col][grid] = missIcon;
                            }
                        }
                        else if (grid == OPPONENT){
                            if (hitGrid[x][y][grid] == 1){ // If hit
                                displayGrid[2*y + row][4*x + col][grid] = hitIcon;
                            }
                            else if (hitGrid[x][y][grid] == 0){ // If not hit
                                displayGrid[2*y + row][4*x + col][grid] = blankIcon;
                            }
                            else if (hitGrid[x][y][grid] == -1){ // If miss
                                displayGrid[2*y + row][4*x + col][grid] = missIcon;
                            }
                        }
                    }
                    else{
                        displayGrid[2*y + row][4*x + col][grid] = gridUnit[row][col];
                    }
                }
            }
        }
    }
}


void DisplayGrids(){ // Display both grids on the screen side-by-side
    UpdateDisplayGrid(PLAYER);
    UpdateDisplayGrid(OPPONENT);
    
    int row, col;
    printf(" ");
    int grid;
    for (grid = 0; grid < 2; grid++){
        for (col = 0; col < 41; col++){ // Print column letters
            if (col%4==0 && col!=0){
                printf("%c", ('A'-1)+col/4);
            }
            else{
                printf(" ");
            }
        }
        printf("         ");
    }

    printf("\n");
    
    for (row = 0; row < 21; row++){ // Print grid spaces
        for (grid = 0; grid < 2; grid++){
            if (row%2==0){
                printf("   ");
            }
            else{
                printf("%2d ", row/2+1); // Print row number
            }
                
            for (col = 0; col < 41; col++){
                int x = col/4;
                int y = row/2;
                if (grid == PLAYER)
                    if (displayGrid[row][col][grid] == shipIcon){
                        if (hitGrid[x][y][grid] == 1){
                           printf("%s%c%s", RED, displayGrid[row][col][grid], WHT); 
                        }
                        else{
                            printf("%c", displayGrid[row][col][grid]);
                        }
                    }
                    else if (displayGrid[row][col][grid] == missIcon){
                        printf("%c", displayGrid[row][col][grid]);
                    }
                    else{
                        printf("%s%c%s", BLU, displayGrid[row][col][grid], WHT);
                    }
                else if (grid == OPPONENT){
                    if (displayGrid[row][col][grid] == hitIcon){
                        printf("%s%c%s", RED, displayGrid[row][col][grid], WHT);
                    }
                    else if (displayGrid[row][col][grid] == missIcon){
                        printf("%c", displayGrid[row][col][grid]);
                    }
                    else{
                        printf("%s%c%s", BLU, displayGrid[row][col][grid], WHT);
                    }
                }
                else{
                    printf("%c", displayGrid[row][col][grid]);
                }
            }
            printf("      ");
        }
        
        printf("\n");
    }
    
    for (grid = 0; grid < 2; grid++){
       if (grid == PLAYER){ // Print grid name
            printf("               Y O U R  G R I D");
        }
        else if (grid == OPPONENT){
            printf("          O P P O N E N T 'S  G R I D");
        } 
        printf("             ");
    }
    
    printf("\n\n");
}

void DisplayTitle(){
  char * title[6] = {
        " ____            _____   _____   _      _____    _____   _    _   _____   _____  ",  
        "|  _ \\     /\\   |_   _| |_   _| | |    |  ___|  / ____| | |  | | |_   _| |  __ \\ ", 
        "| |_) |   /  \\    | |     | |   | |    | |__   | (___   | |__| |   | |   | |__) |",
        "|  _ <   / /\\ \\   | |     | |   | |    |  __|   \\___ \\  |  __  |   | |   |  ___/ ",
        "| |_) | / ____ \\  | |     | |   | |__  | |___   ____) | | |  | |  _| |_  | |     ",
        "|____/ /_/    \\_\\ |_|     |_|   |____| |_____| |_____/  |_|  |_| |_____| |_|     "
    };
    printf("\n");
    int i;
    for (i = 0; i < 6; i++){
        printf("%s\n",title[i]);
    }
    printf("\n");
}