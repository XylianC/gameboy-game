#include <gb/gb.h>
#include "player.h"
#include "map_overworld.h"

Player player;

static const uint8_t movementSpeed = 8;
static const uint8_t spritesize = 8;

void movePlayer(Player *player, uint8_t x, uint8_t y) {
  move_sprite(player->spriteid[0], x, y);
  move_sprite(player->spriteid[1], x + spritesize, y); 
}

uint8_t canPlayerMove(uint8_t newPlayerX, uint8_t newPlayerY) {
    // Calculation of 16px sprite
    int16_t tileX1 = ((int16_t)newPlayerX - 8 + 1) / 8;
    int16_t tileX2 = ((int16_t)newPlayerX - 8 + 14) / 8;
    
    int16_t tileY1 = ((int16_t)newPlayerY - 8) / 8;
    int16_t tileY2 = ((int16_t)newPlayerY - 16 + 15) / 8;
    
    // Allow walking "off-screen" edge to allow transitions
    if (tileX1 < 0 || tileX2 >= 20 || tileY1 < 0 || tileY2 >= 16) {
        return 1;
    }

    // Check all four corners against walkable tiles
    if (isTileSolid(current_map[20 * tileY1 + tileX1])) return 0;
    if (isTileSolid(current_map[20 * tileY1 + tileX2])) return 0;    
    if (isTileSolid(current_map[20 * tileY2 + tileX1])) return 0;
    if (isTileSolid(current_map[20 * tileY2 + tileX2])) return 0;

    return 1;
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

void playerMovement(void) {
  uint8_t pad = joypad();

  if(pad & J_LEFT) {
      if(canPlayerMove(player.x - 8, player.y)) {
        player.x -= movementSpeed;
      }
    } 
    if(pad & J_RIGHT) {
      if(canPlayerMove(player.x + 8, player.y)) {
        player.x += movementSpeed;
      }
    }
    if(pad & J_UP) {
      if(canPlayerMove(player.x, player.y - 8)) {
        player.y -= movementSpeed;
      }
    }
    if(pad & J_DOWN) {
      if(canPlayerMove(player.x, player.y + 8)) {
        player.y += movementSpeed;
      }
    }

    // Screen transitions
    if (player.x >= 152 && current_map_x + 1 < WORLD_WIDTH)  {
      loadMap(current_map_x + 1, current_map_y, 16, player.y);
    } else if (player.x <= 8 && current_map_x > 0)  {
      loadMap(current_map_x - 1, current_map_y, 144, player.y);
    } else if (player.y >= 128 && current_map_y + 1 < WORLD_HEIGHT)  {
      loadMap(current_map_x , current_map_y + 1, player.x, 24);
    } else if (player.y <= 16 && current_map_y > 0)  {
      loadMap(current_map_x, current_map_y - 1, player.x, 120);
    }

    // World border clamping
    if (current_map_x == 0 && player.x < 8) player.x = 8;
    if (current_map_x == WORLD_WIDTH - 1 && player.x > 152) player.x = 152;
    if (current_map_y == 0 && player.y < 16) player.y = 16;
    if (current_map_y == WORLD_HEIGHT - 1 && player.y > 128) player.y = 128;

    movePlayer(&player, player.x, player.y);
}
