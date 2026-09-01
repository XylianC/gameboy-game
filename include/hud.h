#ifndef HUD_H
#define HUD_H

#include <gb/gb.h>
#include <stdint.h>

#define HUD_WIDTH   12
#define HUD_HEIGHT  2

void initHud(const char *playerName, uint8_t initialLevel);

void hud_update_level(uint8_t level);
void hud_update_name(const char *playerName);

uint8_t charToTile(char c);

#endif
