#ifndef NPC_H
#define NPC_H

#include <gb/gb.h>
#include <stdint.h>

typedef enum {
  NPC_TYPE_STATIC,
  NPC_TYPE_WANDER,
  NPC_TYPE_TALKONLY
} NPCType;

typedef struct {
  uint8_t spriteid[2];
  uint8_t x;
  uint8_t y;
  uint8_t mapX;
  uint8_t mapY;
  const char *dialogue;
  NPCType type;
} NPC;

extern NPC test_npc;

void setupNPCs(void);
void moveNPC(NPC *targetNPC, uint8_t horizontalMovement, uint8_t verticalMovement);
void updateNPC(NPC *targetNPC);
void checkNPCInteraction(NPC *targetNPC);
uint8_t checkPlayerNPCCollision(uint8_t target_x, uint8_t target_y, NPC *targetNPC);


#endif
