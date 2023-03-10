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

int PlaceShip(int ship, int grid, int orient, int row, int col){
    int canPlace = 0;

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
    
    return canPlace;
}

void DrawGrid(int grid){
    int y;
    for (y = 0; y < SIZE; y++){
        int x;
        for (x = 0; x < SIZE; x++){
            printf("%d ", shipGrid[x][y][grid]);
        }
        printf("\n");
    }

}

void DrawHitGrid(int grid){
    int y;
    for (y = 0; y < SIZE; y++){
        int x;
        for (x = 0; x < SIZE; x++){
            printf("%d ", hitGrid[x][y][grid]);
        }
        printf("\n");
    }

}

void RandomPlace(int ship, int grid){
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

int Hit(int row, char col, int grid){
    if (shipGrid[row][col-65][grid] != 0){
        hitGrid[row][col-65][grid] = 1;
        return 1;
    }
    else{
        return 0;
    }
}

int IsDestroyed(int ship, int grid){
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
    printf("\n%d\n",hits);
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
    
    int i;
    for (i = 1; i <= 5; i++){
        RandomPlace(i, PLAYER);
    }
    
    DrawGrid(PLAYER);
    printf("\n");
    int y, isHit;
    for (y = 0; y < SIZE; y++){
        int x;
        for (x = 65; x < SIZE + 65; x++){
            isHit = Hit(y, x, PLAYER);
        }
    }
    DrawHitGrid(PLAYER);
    printf("\n%d",IsDestroyed(BATTLESHIP, PLAYER));

    return 0;
}

