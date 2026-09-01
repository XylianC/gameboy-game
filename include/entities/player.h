#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>
#include <stdint.h>

typedef struct {
  uint8_t spriteid[2];
  uint8_t x;
  uint8_t y;
  uint8_t width;
  uint8_t height;
} Player;

extern Player player;

void setupPlayer(void);
void playerMovement(void);

#endif
