#include <gb/gb.h>
#include <stdio.h>
#include <gbdk/font.h>
#include "../include/common.h"
#include "../gen/maps/overworld_test.h"
#include "../gen/tiles/tileset.h"
#include "../gen/sprites/playerSprite.h"
#include "entities/player.c"
#include "../gen/hud/hud.h"


#include "../gen/maps/overworld_test2.h"

const unsigned char *current_map;
uint8_t current_map_id = 0;

const uint8_t tile_collision_table[256] = {
    [0x2D] = 1, //water tile
};

uint8_t isTileSolid(uint8_t tile_id) {
    return tile_collision_table[tile_id];
}

struct Player player;
uint8_t spritesize = 8;

uint8_t canPlayerMove(uint8_t newPlayerX, uint8_t newPlayerY) {
    uint16_t tileX1 = (newPlayerX - 8) / 8;
    uint16_t tileY1 = (newPlayerY - 16) / 8;
    uint16_t tileX2 = (newPlayerX - 8 + 15) / 8; // right edge
    uint16_t tileY2 = (newPlayerY - 16 + 15) / 8; // bottom edge

    // Check bounds to prevent reading outside the overworld_test array
    if (tileX1 >= 20 || tileX2 >= 20 || tileY1 >= 16 || tileY2 >= 16) {
        return 0;
    }

    // Check all four corners against walkable tiles
    if (isTileSolid(overworld_test[20 * tileY1 + tileX1])) return 0;
    if (isTileSolid(overworld_test[20 * tileY1 + tileX2])) return 0;    
    if (isTileSolid(overworld_test[20 * tileY2 + tileX1])) return 0;
    if (isTileSolid(overworld_test[20 * tileY2 + tileX2])) return 0;

    return 1;
}

void performantDelay(uint8_t loops) {
  uint8_t i;
  for(i = 0; i < loops; i++) {
    wait_vbl_done();
  }
}

void movePlayer(struct Player* player, uint8_t x, uint8_t y) {
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

void loadMap(uint8_t map_id, uint8_t startX, uint8_t startY) {
  current_map_id = map_id;

  if (map_id == 0) {
    current_map = overworld_test;
  } else {
    current_map = overworld_test2;
  }

  set_bkg_tiles(0, 0, 20, 16, current_map);
  player.x = startX;
  player.y = startY; 
  movePlayer(&player, player.x, player.y);
}

void main() {
  font_t min_font;

  font_init();
  min_font = font_load(font_min);
  font_set(min_font);
  // min font is exactly 36 chars, so tiles need to be loaded at 36 offset
  
  const char *playerName = "Xylian";
  uint8_t level = 4;
  uint8_t magic = 3;
  uint8_t power = 2;

  uint8_t pauseMenu = 0;
  
  // BACKGROUND
  set_bkg_data(36, 18, tileset);
  loadMap(0, 80, 70);

  // BKG_HEIGHT:    16 * 8 = 128px
  // SCREEN_WIDTH:  20 * 8 = 160px
  // HUD:           2 * 8 = 16px 
  // GB RESOLUTION: 160x144px
  
  // HUD
  set_win_tiles(0,0,12,2, hud);
  move_win(6, 128);

  // SPRITES
  SPRITES_8x16;
  set_sprite_data(0, 4, player_sprite);
  setupPlayer();

  SHOW_BKG;
  SHOW_SPRITES;
  SHOW_WIN;
  DISPLAY_ON;

  uint8_t movementSpeed = 8;

  while(1) {
    if(joypad() & J_LEFT) {
      if(canPlayerMove(player.x - 8, player.y)) {
        player.x -= movementSpeed;
      }
    } 
    if(joypad() & J_RIGHT) {
      if(canPlayerMove(player.x + 8, player.y)) {
        player.x += movementSpeed;
      }
    }
    if(joypad() & J_UP) {
      if(canPlayerMove(player.x, player.y - 8)) {
        player.y -= movementSpeed;
      }
    }
    if(joypad() & J_DOWN) {
      if(canPlayerMove(player.x, player.y + 8)) {
        player.y += movementSpeed;
      }
    }

    if (player.x >= 152 && current_map_id == 0)  {
      loadMap(1, 16, player.y);
    }

    else if (player.x <= 8 && current_map_id == 1) {
      loadMap(0, 144, player.y);
    }


    movePlayer(&player, player.x, player.y);
    
    performantDelay(8);
  }
}
