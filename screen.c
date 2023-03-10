/*******************************************************************************
* File: 
* Author(s):
* Purpose: 
* Version:	1.0 - 
* Resources: 
*******************************************************************************/
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define WIDTH 120
#define HEIGHT 40

void DisplayScreen(char screen[HEIGHT+1][WIDTH+1]){
  int y;
  for (y = 0; y < HEIGHT; y++){
    int x;
    for (x = 0; x < WIDTH; x++){
      printf("%c", screen[y][x]); 
    }
    printf("\n");
  }
}

void ClearScreen(){
  int y;
  for (y = 0; y < HEIGHT; y++){
      printf("\x1b[1F"); // Move to beginning of previous line
      printf("\x1b[2K"); // Clear entire line
  }
}

void Refresh(char screen[HEIGHT+1][WIDTH+1]){
  ClearScreen();
  DisplayScreen(screen);
}

void DrawSin(int amp, int freq, int phase, int pos, int b1, int b2, char (*screen)[HEIGHT+1][WIDTH+1]){
  int x;
  int start = (b1<0)?0:b1;
  int end = (b2>WIDTH)?WIDTH:b2;
  for (x = start; x < end; x++){
    int y = round((float)amp*sin((float)freq*(float)x + (float)phase) + (float)pos);
    (*screen)[y][x] = '1';
  }
}

int main(){
  char screen[HEIGHT+1][WIDTH+1];
  int y;
  for (y = 0; y < HEIGHT; y++){
    int x;
    for (x = 0; x < WIDTH; x++){
      screen[y][x] = '.';
    }
  }
  
  Refresh(screen);
  
  DrawSin(1, 1, 1, 10, 10, 40, &screen);
  
  Refresh(screen);
  
  /*
  clock_t start_t, end_t;
  while (1){
    double dt;
    end_t = clock();
    dt = (double)(end_t - start_t);
    start_t = clock();
    
    printf("%f\n", dt);
  }
  */
  
	return 0;
}
