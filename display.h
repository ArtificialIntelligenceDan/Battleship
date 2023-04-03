/*******************************************************************************
* File: display.h
* Dependencies: grids.h
*
* Purpose: Contains functions and variables used to display information on the 
*          screen.
* 
* Course: CS125
* Version:	1.0 - 4/3/23 - Aidan Kihm
*
* Resources: 
* https://textkool.com/en/ascii-art-generator?hl=default&vl=default&font=
*   Red%20Phoenix&text=Your%20text%20here%20
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

// Display Variables
char gridUnit[3][5] = {"+---+",
                       "|   |",
                       "+---+"};
char missIcon = '.';
char hitIcon = 'X';
char blankIcon = ' ';
char shipIcon = 'O';

char displayGrid[21][41][2];

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
    printf("\n ");
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
