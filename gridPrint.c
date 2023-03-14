#include <stdio.h>

char gridUnit[3][5] = {"+---+",
                       "| . |",
                       "+---+"};

char grid[21][41];

void DisplayGrids(){
    int row, col;
    printf(" ");
    for (col = 0; col < 41; col++){
        if (col%4==0 && col!=0){
            printf("%c", ('A'-1)+col/4);
        }
        else{
            printf(" ");
        }
    }
    printf("        ");
    for (col = 0; col < 41; col++){
        if (col%4==0 && col!=0){
            printf("%c", ('A'-1)+col/4);
        }
        else{
            printf(" ");
        }
    }
    printf("\n");
    
    for (row = 0; row < 21; row++){
        if (row%2==0){
            printf("   ");
        }
        else{
            printf("%2d ", row/2+1);
        }
        
        for (col = 0; col < 41; col++){
            printf("%c", grid[row][col]);
        }
        printf("     ");
        if (row%2==0){
            printf("   ");
        }
        else{
            printf("%2d ", row/2+1);
        }
        for (col = 0; col < 41; col++){
            printf("%c", grid[row][col]);
        }
        printf("\n");
    }
}

int main()
{
    int y;
    for (y = 0; y < 10; y++){
        int x;
        for (x = 0; x < 10; x++){
            int row;
            for (row = 0; row < 3; row++){
                int col;
                for (col = 0; col < 5; col++){
                    grid[2*y + row][4*x + col] = gridUnit[row][col];
                }
            }
        }
    }
    
    DisplayGrids();

    return 0;
}
