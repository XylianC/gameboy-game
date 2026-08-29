#include <gb/gb.h>
#include <stdio.h>
#include "../include/head.c"
#include "../include/backgroundtiles.c"
#include "../include/testmap.c"


void main() {
  const char *playerName = "Xylian";
  int level = 4;
  int magic = 3;
  int power = 2;

  int pauseMenu = 0;
  
  // Load Sprite from included head.c file
  set_sprite_data(0, 0, head_td);
  set_sprite_tile(0, 0);
  move_sprite(0, 88, 78);  

  set_bkg_data(0, 7, backgroundtiles);
  set_bkg_tiles(0, 0, 20, 18, testmap);

  
  SHOW_BKG;
  SHOW_SPRITES;
  DISPLAY_ON;

  while(1) {

    // Movement Code // 
    switch(joypad()) {
      case J_LEFT: 
        scroll_sprite(0, -10, 0);
        break;
      case J_RIGHT:
        scroll_sprite(0, 10, 0);
        break;
      case J_UP: 
        scroll_sprite(0, 0, -10);
        break;
      case J_DOWN: 
        scroll_sprite(0, 0, 10);
        break;
    }
    delay(150);


    wait_vbl_done();
  }
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
