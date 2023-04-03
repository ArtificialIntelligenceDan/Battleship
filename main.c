//Code written by Marcos
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "grids.h"
#include "display.h"


int main()
{
    srand(time(NULL));
    DisplayTitle();              //Displaying Title and Placing Opponent Ships
    sleep(3);
    FILE *scoreBoard;
    RandomPlaceAll(OPPONENT);
    DisplayGrids();
    int i, smartHit, highScore, orientation, row, rowCheck, orientationCheck, placeCheck;
    char col;
    int canPlace = 0;
    int ansPlace = 0;
    int score = 0;
    int carCount = 0;
    int crCount = 0;
    int bCount = 0;
    int sCount = 0;
    int dCount = 0;
    int carCountO = 0;
    int crCountO = 0;
    int bCountO = 0;
    int sCountO = 0;
    int dCountO = 0;

    scoreBoard = fopen("scoreBoard.txt", "r");                      //read and writes to another file to keep highscore
    int matches = fscanf(scoreBoard, "%d", &highScore);
    if(matches > 0)
        printf("The Current Highscore is %d\n", highScore);
    else{
        printf("There is no Current High Score");
        highScore = 1000;
    }  
    fclose(scoreBoard);
    printf("Type 1 to place your own ships or 2 for random ship placement: ");        //Ship Placement
    placeCheck = scanf("%d", &ansPlace);
    while((ansPlace != 1 && ansPlace != 2) || placeCheck != 1){
        printf("TryAgain.\nType 1 to place your own ships or 2 for random ship placement: ");
        placeCheck = scanf("%*c%d", &ansPlace);
    }
    if(ansPlace == 1){
        for(i=1; i<=5; i++){                              //for loop to go through all ships to be placed
            if(i == CARRIER)
                printf("Place your Carrier (Size 5)\n");
            else if(i == BATTLESHIP)
                printf("Place your Battleship (Size 4)\n");
            else if(i == CRUISER)
                printf("Place your Cruiser (Size 3)\n");
            else if(i == SUBMARINE)
                printf("Place your Submarine (Size 3)\n");
            else if(i == DESTROYER)
                printf("Place your DESTROYER (Size 2)\n");
            printf("Type 0 for Horizontal (right) Placement and 1 for Vertical (down) Placement: ");  
            orientationCheck =  scanf("%d", &orientation);                                            //scans for orientation followed by error checking
            while((orientation != 0 && orientation != 1) || orientationCheck != 1){
	        printf("Try Again.\nType 0 for Horizontal (right) Placement and 1 for Vertical (down) Placement: ");
                orientationCheck = scanf("%*c%d", &orientation);
	    }
            printf("Choose a Column: ");    
            scanf("%*c%c", &col);                      //scans in column followed by error checking
	    while(col < 65 || col > 74){
                printf("Try Again.\nChoose a Column: ");
                scanf("%*c%c", &col);
	    } 
            printf("Choose a Row: ");                  //scans in row followed by error checking
            rowCheck = scanf("%d", &row);
	    while(row < 1 || row > 10 || rowCheck != 1){
	        printf("Try Again.\nChoose a Row: ");
                rowCheck = scanf("%*c%d", &row);
	    }
            printf("\n");
            canPlace = 0;
            canPlace = PlaceShip(i, PLAYER, orientation, row-1, col-65);
	    while(canPlace == 0){                                            //checks to make sure ship can be placed where it was told
                printf("THATS NOT ALLOWED!\nTRY AGAIN!\n");
                printf("Type 0 for Horizontal (right) Placement and 1 for Vertical (down) Placement: ");
                orientationCheck = scanf("%d", &orientation);
	        while((orientation != 0 && orientation != 1) || orientationCheck != 1 ){
                    printf("Try Again.\nType 0 for Horizontal (right) Placement and 1 for Vertical (down) Placement: ");
                    orientationCheck = scanf("%*c%d", &orientation);
                }
                printf("Choose a Column: ");                     //scans in column followed by error checking
                scanf("%*c%c", &col);
	        while(col < 65 || col > 74){
                    printf("Try Again.\nChoose a Column: ");
                    scanf("%*c%c", &col);
                }
                printf("Choose a Row: ");                       
                rowCheck = scanf("%d", &row);                  //scans in row followed by error checking
	        while(row < 1 || row > 10 || rowCheck != 1){
                    printf("Try Again.\nChoose a Row: ");
                    rowCheck = scanf("%*c%d", &row);
                }
                printf("\n");
                canPlace = PlaceShip(i, PLAYER, orientation, row-1, col-65);
            }          
            DisplayGrids();
        }
    }
    else if(ansPlace == 2){
        RandomPlaceAll(PLAYER);   //Random Ship placement option
        DisplayGrids();
    }    
    int hitRow, ranRow, ranCol, hit, ranHit;     // Player turn code begins
    char hitCol;
    while(AllSunk(PLAYER) == 0 && AllSunk(OPPONENT) == 0){   //While loop keeps the game going until one board is cleared of ships
        do{                                                  //Do while loop keeps player turn going until they miss
            printf("Choose a Target!\n");  
            printf("Column: ");
            scanf("%*c%c", &hitCol);                       //scans column followed by error checking
            while(hitCol < 65 || hitCol > 74){
                printf("Try Again.\nChoose a Column: ");
                scanf("%*c%c", &hitCol);
            }
            printf("Row: ");
            rowCheck = scanf("%d", &hitRow);                     //scans row followed by error checking
            while(hitRow < 1 || hitRow > 10 || rowCheck != 1){
                printf("Try Again.\nChoose a Row: ");
                rowCheck = scanf("%*c%d", &hitRow);
            }	
            hit = Hit(hitRow-1, hitCol-65, OPPONENT);         //hit function to hit ship
            score++;
            printf("\n");
            DisplayGrids();
            if(hit == 1){                         //if statement to display if a ship was hit or missed
                printf("HIT!!!\n");
            }
            else if(hit == 0){
                printf("MISS!!\n");
            }
            for(i=1; i<=5; i++){                              //Checks for sunken ships to say if player sunk one
                if(IsSunk(i, OPPONENT) == 1){                //for loop goes through all ships, prints which ship sank if one did
	            if(i == 1 && carCount == 0){
                        printf("You Sank My Carrier!\n");
                        carCount++;
                    }
                    if(i == 2 && bCount == 0){
	                printf("You Sank My Battleship!\n");
	                bCount++; 
                    }
	            if(i == 3 && crCount == 0){
                        printf("You Sank My Cruiser!\n");
                        crCount++;
                    }
 	            if(i == 4 && sCount == 0){
                        printf("You Sank My Submarine!\n");
                        sCount++;
                    }
	            if(i == 5 && dCount == 0){
                        printf("You Sank My Destroyer!\n");
 	                dCount++;
	            }
                }
            }
            if(AllSunk(PLAYER) == 1 || AllSunk(OPPONENT) == 1)    //two if statements with breaks to leave the game loop if the game is finished
	        break;
        }while(hit == 1);
        if(AllSunk(PLAYER) == 1 || AllSunk(OPPONENT) == 1)
            break;
        sleep(1.5);
        printf("Opponents turn\n");
        sleep(1.5);			                //Computer Turn begins with another do while loop to keep them going when they hit
        do{
            smartHit = SmartHit(PLAYER);            //smart hit function allows the opponent to not guess randomly when they hit a ship before     
            if(smartHit == 1){
                DisplayGrids();
                printf("OPPONENT HIT A SHIP!!! \nOPPONENT TAKING ANOTHER TURN\n");  //if statements to print the opponent missed or hit
	        sleep(1.5);
            }
            else if(smartHit == 0){
	        DisplayGrids();
                printf("OPPONENT MISSED YOUR SHIP!!\n");
            }
            for(i=1; i<=5; i++){                          //Checks if a player boat was sunk and displays if one is
                if(IsSunk(i, PLAYER) == 1){
                    if(i == 1 && carCountO == 0){
                        printf("Your Carrier Sank!\n");
                        carCountO++;
                    }
                    if(i == 2 && bCountO == 0){
                        printf("Your Battleship Sank!\n");
                        bCountO++;
                    }
                    if(i == 3 && crCountO == 0){
                        printf("Your Cruiser Sank!\n");
                        crCountO++;
                    }
                    if(i == 4 && sCountO == 0){
                        printf("Your Submarine Sank!\n");
                        sCountO++;
                    }
                    if(i == 5 && dCountO == 0){
                        printf("Your Destroyer Sank!\n");
                        dCountO++;
                    }
                }
            }
            sleep(1.5);
            if(AllSunk(PLAYER) == 1 || AllSunk(OPPONENT) == 1)
                break;    
        }while(smartHit == 1);                                  //end of do while loop for opponent, checks if they hit
    }
    if(score < highScore){                                   //checks if the number of turns is less that the previous best score, displays if lower
        fopen("scoreBoard.txt", "w");
        fprintf(scoreBoard, "%d", highScore);
        fclose(scoreBoard); 
    } 
    printf("GAME OVER!\n");                   //  Prints game over
    if(AllSunk(PLAYER) == 1)                 // if and else if statement decides if players or opponents ship sank and prints you won or you lost
        printf("YOU LOST!\n");
    else if(AllSunk(OPPONENT) == 1)
        printf("YOU WON!\n");
return 0;
}
