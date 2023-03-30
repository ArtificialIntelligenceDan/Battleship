#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "functions.h"

int main()
{
    srand(time(NULL));



    RandomPlaceAll(OPPONENT);

    DisplayGrids();
    int i, ansPlace = 0, orientation, row, canPlace = 0;
    char col;

    while(ansPlace != 1 && ansPlace != 2)
    {
        printf("Type 1 to place your own ships or 2 for random ship placement: ");
        scanf("%d", &ansPlace);
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
            scanf("%d", &orientation);
            printf("Choose a Column: ");
            scanf("%*c%c", &col);
            printf("Choose a Row: ");
            scanf("%d", &row);
            printf("\n");
            canPlace = 0;
            canPlace = PlaceShip(i, PLAYER, orientation, row-1, col-65);
	    while(canPlace == 0){
              printf("THATS NOT ALLOWED!\nTRY AGAIN!");
              printf("Type 0 for Horizontal (right) Placement and 1 for Vertical (down) Placement: ");
              scanf("%d", &orientation);
              printf("Choose a Column: ");
              scanf("%*c%c", &col);
              printf("Choose a Row: ");
              scanf("%d", &row);
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

    do{
      printf("Choose a Target!\n");  //Player Turn
      printf("Column: ");
      scanf("%*c%c", &hitCol);
      printf("Row: ");
      scanf("%d", &hitRow);
      hit = Hit(hitRow-1, hitCol-65, OPPONENT);
      DrawHitGrid(OPPONENT);
      if(hit == 1){
        printf("HIT!!!\n");
      }
      else if(hit == 0){
        printf("MISS!!\n");
      }
      DisplayGrids();
      for(i=1; i<=5; i++){
        if(IsSunk(i, OPPONENT) == 1){
          
	  if(i == 1)
           printf("You Sank My Carrier!");
          if(i == 2)
	   printf("You Sank My Battleship!");
	  if(i == 3)
           printf("You Sank My Cruiser!");
          if(i == 4)
           printf("You Sank My Submarine!");
	  if(i == 5)
           printf("You Sank My Destroyer!");
        }
      }
    }while(hit == 1);

    printf("Opponents turn\n");
    do{
      ranRow = rand()%9+0;
      ranCol = rand()%9+0;
      ranHit = Hit(ranRow, ranCol, PLAYER);
      printf("Player Hit Grid: \n");
      DrawHitGrid(PLAYER);
      
      if(ranHit == 1){
        printf("OPPONENT HIT A SHIP!!!\nOPPONENT TAKING ANOTHER TURN.");
      }
      else if(ranHit == 0){
        printf("OPPONENT MISSED YOUR SHIP\n!!");
      }
     }while(ranHit == 1);

      
    return 0;
}
