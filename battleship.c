#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

// Grids
const int OPPONENT = 0;
const int PLAYER = 1;

// Ships
const int CARRIER = 1;
const int BATTLESHIP = 2;
const int CRUISER = 3;
const int SUBMARINE = 4;
const int DESTROYER = 5;

const int LENGTH[6] = {0, 5,4,3,3,2};
//         placeholder ^

// Orientations
const int HORIZONTAL = 0;
const int VERTICAL = 1;

int shipGrid[SIZE][SIZE][2];
//           ROWS  COLS  ^ 0=Opponent 1=Player
int hitGrid[SIZE][SIZE][2];

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
                    shipGrid[col][y][grid] = ship; // Place ship in slots
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

int Hit(int row, char col, int grid){ // Check if space has been hit
    if (shipGrid[row][col-65][grid] != 0){
        hitGrid[row][col-65][grid] = 1;
        return 1;
    }
    else{
        return 0;
    }
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

int main()
{
    srand(time(NULL));
    
    
    
    RandomPlaceAll(OPPONENT);
    
    DrawGrid(PLAYER);
    int i, ansPlace = 0, orientation, row;
    char col;
    
    while(ansPlace != 1 && ansPlace != 2)
    {    
        printf("Type 1 to place your own ships or 2 for random ship placement: ");
        scanf("%d", &ansPlace);
    }
    if(ansPlace == 1)
    {
        for(i=1; i=5; i<=5)
        {
            if(i == CARRIER)
                printf("Place your Carrier (Size 5)\n");
            else if(i = BATTLESHIP)
                printf("Place your Battleship (Size 4)\n");
            else if(i = CRUISER)
                printf("Place your Cruiser (Size 3)\n");
            else if(i = SUBMARINE)
                printf("Place your Submarine (Size 3)\n");
            else if(i = DESTROYER)
                printf("Place your DESTROYER (Size 2)\n");
            printf("Type 0 for Horizontal (right) Placement and 1 for Vertical (down) Placement: ");
            scanf("%d", &orientation);
            printf("Choose a Column: ");
            scanf("%*c%c", &col);
            printf("Choose a Row: ");
            scanf("%d", &row);
            PlaceShip(i, PLAYER, orientation, row-1, col-65);
        }
    }
    else if(ansPlace == 2)
    {
        RandomPlaceAll(PLAYER);
    }
    DrawGrid(PLAYER);
    return 0;
}

