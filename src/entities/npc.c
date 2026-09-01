#include <gb/gb.h>
#include <stdint.h>
#include "npc.h"
#include "player.h"
#include "map_overworld.h"

extern const unsigned char player_sprite[];
const uint8_t spriteWidth = 8;

NPC test_npc;

void setupNPCs(void) {
  set_sprite_data(4, 4, player_sprite);

  test_npc.mapX = 1;
  test_npc.mapY = 0;
  test_npc.x = 80;
  test_npc.y = 80;

  test_npc.dialogue = "Its dangerous to go alone!";

  test_npc.spriteid[0] = 2;
  test_npc.spriteid[1] = 3;

  test_npc.type = NPC_TYPE_STATIC;
 
  set_sprite_tile(2, 4);
  set_sprite_tile(3, 6);

  updateNPC(&test_npc);
}

void updateNPC(NPC *targetNPC) {
    // Check if the player is in the same map room as this NPC
    if (current_map_x == targetNPC->mapX && current_map_y == targetNPC->mapY) {
        // Place the sprite on screen (left half + right half)
        move_sprite(targetNPC->spriteid[0], targetNPC->x, targetNPC->y);
        move_sprite(targetNPC->spriteid[1], targetNPC->x + spriteWidth, targetNPC->y);
    } else {
        // Hide sprites off-screen when the player is in a different room
        move_sprite(targetNPC->spriteid[0], 0, 0);
        move_sprite(targetNPC->spriteid[1], 0, 0);
    }
}

void moveNPC(NPC *targetNPC, uint8_t horizontalMovement, uint8_t verticalMovement) {
  targetNPC->x = targetNPC->x + horizontalMovement; 
  targetNPC->y = targetNPC->y + verticalMovement;

  move_sprite(targetNPC->spriteid[0], targetNPC->x, targetNPC->y);
  move_sprite(targetNPC->spriteid[1], targetNPC->x + spriteWidth, targetNPC->y);
}

void checkNPCInteraction(NPC *targetNPC) {
    // Only check if player is in the same room
    if (current_map_x != targetNPC->mapX || current_map_y != targetNPC->mapY) {
        return;
    }

    // Distance calculation relative to the NPC
    int16_t dx = (int16_t)player.x - (int16_t)targetNPC->x;
    int16_t dy = (int16_t)player.y - (int16_t)targetNPC->y;

    // Check if player is standing adjacent (within 1 tile / 16px) and presses A
    if ((dx >= -16 && dx <= 16) && (dy >= -16 && dy <= 16)) {
        if (joypad() & J_A) {
            // Interaction triggered
            // DEBUG CODE: (So this actually works, next up )
            moveNPC(targetNPC, 8, 8);
            
        }
    
    }
}

uint8_t checkPlayerNPCCollision(uint8_t target_x, uint8_t target_y, NPC *targetNPC) {
    // If not in the same room, no collision is possible
    if (current_map_x != targetNPC->mapX || current_map_y != targetNPC->mapY) {
        return 0;
    }

    // 16x16 Bounding Box Overlap Check:
    // Overlap occurs when |target_x - npc_x| < 16 AND |target_y - npc_y| < 16
    int16_t dx = (int16_t)target_x - (int16_t)targetNPC->x;
    int16_t dy = (int16_t)target_y - (int16_t)targetNPC->y;

    if ((dx > -16 && dx < 16) && (dy > -16 && dy < 16)) {
        return 1; // Collision detected
    }

    return 0; // Clear
}
