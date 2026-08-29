#include <gb/gb.h>
#include <stdio.h>

void main() {
  const char *playerName = "Xylian";
  int level = 4;
  int magic = 3;
  int power = 2;

  printf("HELLO WORLD\n");
  printf("TESTING\n");
  printf("Hi %s, it's nice to meet you, welcome to our village!\n", playerName);



  printf("\n- PLAYER -\n");
  printf("%s\n", playerName);
  printf("LEVEL: %d\n", level);
  printf("MAGIC: %d\n", magic);
  printf("POWER: %d\n", power);
  printf("----------\n");

}

// Structure of gameloop
//
// void main() {
//  initialise_game() ---- Loads tiles and variables
//  
//  while (1) { ---- THIS ENTIRE LOOP IS 1 FRAME
//    update_game_logic() --- Player Movement, Enemies...
//
//    wait_vbl_done(); --- Pause CPU until screen is finished drawing
//
//    update_graphics(); ---- Update graphics :o
//  }
//
// }
