#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "functions.h"

int main()
{
    srand(time(NULL));



    RandomPlaceAll(OPPONENT);

    DisplayGrids();
    int i, ansPlace = 0, orientation, row, canPlace = 0, rowCheck, orientationCheck, placeCheck;
    char col;
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

    printf("Type 1 to place your own ships or 2 for random ship placement: ");
    placeCheck = scanf("%d", &ansPlace);
    while((ansPlace != 1 && ansPlace != 2) || placeCheck != 1)
    {
      printf("TryAgain.\nType 1 to place your own ships or 2 for random ship placement: ");
      placeCheck = scanf("%*c%d", &ansPlace);

    }
    if(ansPlace == 1)
    {
        for(i=1; i<=5; i++)
        {
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
            orientationCheck =  scanf("%d", &orientation);
            while((orientation != 0 && orientation != 1) || orientationCheck != 1){
	      printf("Try Again.\nType 0 for Horizontal (right) Placement and 1 for Vertical (down) Placement: ");
              orientationCheck = scanf("%*c%d", &orientation);
	    }
            printf("Choose a Column: ");
            scanf("%*c%c", &col);
	    while(col < 65 || col > 74){
              printf("Try Again.\nChoose a Column: ");
              scanf("%*c%c", &col);
 	    } 
            printf("Choose a Row: ");
            rowCheck = scanf("%d", &row);
	    while(row < 1 || row > 10 || rowCheck != 1){
	      printf("Try Again.\nChoose a Row: ");
              rowCheck = scanf("%*c%d", &row);
	    }
            printf("\n");
            canPlace = 0;
            canPlace = PlaceShip(i, PLAYER, orientation, row-1, col-65);
	    while(canPlace == 0){
              printf("THATS NOT ALLOWED!\nTRY AGAIN!\n");
              printf("Type 0 for Horizontal (right) Placement and 1 for Vertical (down) Placement: ");
              orientationCheck = scanf("%d", &orientation);
	      while((orientation != 0 && orientation != 1) || orientationCheck != 1 ){
                printf("Try Again.\nType 0 for Horizontal (right) Placement and 1 for Vertical (down) Placement: ");
                orientationCheck = scanf("%*c%d", &orientation);
              }
              printf("Choose a Column: ");
              scanf("%*c%c", &col);
	      while(col < 65 || col > 74){
                printf("Try Again.\nChoose a Column: ");
                scanf("%*c%c", &col);
              }
              printf("Choose a Row: ");
              rowCheck = scanf("%d", &row);
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

    else if(ansPlace == 2)
    {
        RandomPlaceAll(PLAYER);
        DisplayGrids();
    }

    int hitRow, ranRow, ranCol, hit, ranHit;     // Player turn
    char hitCol;
    printf("Done\n");
    DrawGrid(OPPONENT);

    while(AllSunk(PLAYER) == 0 && AllSunk(OPPONENT) == 0){

    do{
      printf("Choose a Target!\n");  //Player Turn
      printf("Column: ");
      scanf("%*c%c", &hitCol);
      while(hitCol < 65 || hitCol > 74){
        printf("Try Again.\nChoose a Column: ");
        scanf("%*c%c", &hitCol);
      }
      printf("Row: ");
      rowCheck = scanf("%d", &hitRow);
      while(hitRow < 1 || hitRow > 10 || rowCheck != 1){
        printf("Try Again.\nChoose a Row: ");
        rowCheck = scanf("%*c%d", &hitRow);
      }
	
      hit = Hit(hitRow-1, hitCol-65, OPPONENT);
      DrawHitGrid(OPPONENT);
      DisplayGrids();
      if(hit == 1){
        printf("HIT!!!\n");
      }
      else if(hit == 0){
        printf("MISS!!\n");
      }
      for(i=1; i<=5; i++){
        if(IsSunk(i, OPPONENT) == 1){          
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
    }while(hit == 1);
    sleep(1.5);
    printf("Opponents turn\n");
    sleep(1.5);			      //Computer Turn
    do{
      ranRow = rand()%9+0;
      ranCol = rand()%9+0;
      ranHit = Hit(ranRow, ranCol, PLAYER);
      
      if(ranHit == 1){
	DisplayGrids();
        printf("OPPONENT HIT A SHIP!!! \nOPPONENT TAKING ANOTHER TURN\n");
	sleep(1.5);
      }
      else if(ranHit == 0){
	DisplayGrids();
        printf("OPPONENT MISSED YOUR SHIP!!\n");
      }
      for(i=1; i<=5; i++){
        if(IsSunk(i, OPPONENT) == 1){
          if(i == 1 && carCountO == 0){
            printf("You Sank My Carrier!\n");
            carCountO++;
          }
          if(i == 2 && bCountO == 0){
            printf("You Sank My Battleship!\n");
            bCountO++;
          }
          if(i == 3 && crCountO == 0){
            printf("You Sank My Cruiser!\n");
            crCountO++;
          }
          if(i == 4 && sCountO == 0){
            printf("You Sank My Submarine!\n");
            sCountO++;
          }
          if(i == 5 && dCountO == 0){
            printf("You Sank My Destroyer!\n");
            dCountO++;
          }
        }
      }
      sleep(1.5);    
    }while(ranHit == 1);
  }

  printf("GAME OVER!");
  if(AllSunk(PLAYER) == 1)
    printf("YOU LOST!");
  else if(AllSunk(OPPONENT) == 1)
    printf("YOU WON!");
  
return 0;
}
