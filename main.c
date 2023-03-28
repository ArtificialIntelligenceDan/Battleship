#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "functions.h"

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
        for(i=1; i<=5; i++)
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
            DrawGrid(PLAYER);

         }
}
    else if(ansPlace == 2)
    {
        RandomPlaceAll(PLAYER);
        DrawGrid(PLAYER);
    }

    int hitRow;     // Player turn
    char hitCol;
int hit;
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
        printf("MISS!!");
      }
     }while(hit == 1);

    return 0;
}