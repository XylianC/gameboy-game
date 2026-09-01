#include <gb/gb.h>
#include <stdint.h>

#include "map_overworld.h"
#include "player.h"
#include "npc.h"
#include "maps/overworld_y1x1.h"
#include "maps/overworld_y1x2.h"
#include "maps/overworld_y2x1.h"
#include "maps/overworld_y2x2.h"

#include "tileset.h"

const unsigned char *current_map;
uint8_t current_map_x = 1;
uint8_t current_map_y = 1;

const unsigned char * const overworld_grid[WORLD_HEIGHT][WORLD_WIDTH] = {
  { overworld_y1x1, overworld_y1x2 },
  { overworld_y2x1, overworld_y2x2 }
};

const uint8_t tile_collision_table[256] = {
    [0x2D] = 1,   // WATER TILE
    [0x2A] = 1,   // WALL TILE
    [0x2B] = 1,   // WALL TILE
    [0x2C] = 1,   // WALL TILE
};

uint8_t isTileSolid(uint8_t tile_id) {
    return tile_collision_table[tile_id];
}

void loadMap(uint8_t mapX, uint8_t mapY, uint8_t startX, uint8_t startY) {
  if(mapX >= WORLD_WIDTH || mapY >= WORLD_HEIGHT) return;

  current_map_x = mapX;
  current_map_y = mapY;
  current_map = overworld_grid[mapY][mapX];


  set_bkg_tiles(0, 0, 20, 16, current_map);
  
  player.x = startX;
  player.y = startY; 

  updateNPC(&test_npc);
}

void initOverworld(void) {
  set_bkg_data(36, 24, tileset);
  loadMap(0, 0, 80, 70);
}
