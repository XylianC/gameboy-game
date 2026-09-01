#ifndef MAP_OVERWORLD_H
#define MAP_OVERWORLD_H

#include <gb/gb.h>
#include <stdint.h>

#define WORLD_WIDTH   2
#define WORLD_HEIGHT  2

extern const unsigned char *current_map;
extern uint8_t current_map_x;
extern uint8_t current_map_y;

void initOverworld(void);
void loadMap(uint8_t mapX, uint8_t mapY, uint8_t startX, uint8_t startY);
uint8_t isTileSolid(uint8_t tile_id);

#endif
