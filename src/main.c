#include <gb/gb.h>
#include <stdio.h>
#include <gbdk/font.h>

#include "hud.h"

#include "player.h"

#include "map_overworld.h"
#include "tileset.h"

void performantDelay(uint8_t loops) {
  uint8_t i;
  for(i = 0; i < loops; i++) {
    wait_vbl_done();
  }
}

void main(void) {
  font_t min_font;

  font_init();
  min_font = font_load(font_min);
  font_set(min_font);
  // min font is exactly 36 chars, so tiles need to be loaded at 36 offset
  initOverworld();
  
  // HUD
  hud_init("Stinky", 4);
  // SPRITES
  setupPlayer();

  SHOW_BKG;
  SHOW_SPRITES;
  SHOW_WIN;
  DISPLAY_ON;


  while(1) {
    playerMovement();

    performantDelay(8);
  }
}
