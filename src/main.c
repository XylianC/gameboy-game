#include <gb/gb.h>
#include <stdio.h>
#include "../include/common.h"
#include "../gen/maps/testmap.h"
#include "../gen/tiles/background_tiles.h"
#include "../gen/sprites/playerSprite.h"
#include "entities/player.c"

struct Player player;
UBYTE spritesize = 8;

void movePlayer(struct Player* player, UINT8 x, UINT8 y) {
  move_sprite(player->spriteid[0], x, y);
  move_sprite(player->spriteid[1], x + spritesize, y); 
}

void setupPlayer() {
  player.x = 80;
  player.y = 70;
  player.width = 16;
  player.height = 16;

  set_sprite_tile(0, 0);
  player.spriteid[0] = 0;
  set_sprite_tile(1, 2);
  player.spriteid[1] = 1;

  movePlayer(&player, player.x, player.y);
}


void main() {
  const char *playerName = "Xylian";
  int level = 4;
  int magic = 3;
  int power = 2;

  int pauseMenu = 0;
  
  set_bkg_data(0, 16, background_tiles);
  set_bkg_tiles(0, 0, 20, 16, testmap); 

  // BKG_HEIGHT:    16 * 8 = 128px
  // SCREEN_WIDTH:  20 * 8 = 160px
  // HUD:           2 * 8 = 16px 
  // GB RESOLUTION: 160x144px
  

  SPRITES_8x16;
  
  set_sprite_data(0, 4, player_sprite);
  setupPlayer();

  SHOW_SPRITES;
  SHOW_BKG;
  DISPLAY_ON;

  UINT8 movementSpeed = 1;

  while(1) {
    if(joypad() & J_LEFT) {
      player.x -= movementSpeed;
    } 
    if(joypad() & J_RIGHT) {
      player.x += movementSpeed;
    }
    if(joypad() & J_UP) {
      player.y -= movementSpeed;
    }
    if(joypad() & J_DOWN) {
      player.y += movementSpeed;
    }

    movePlayer(&player, player.x, player.y);

    wait_vbl_done();
  }
}
