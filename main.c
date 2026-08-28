#include <gb/gb.h>
#include <stdint.h>

// Simple 8x8 pixel tile data (1 tile for player, 1 for solid wall, 1 for floor)
const uint8_t tile_data[] = {
    // Tile 0: Blank Floor
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    // Tile 1: Solid Wall Box
    0xFF,0xFF,0x81,0x81,0x81,0x81,0x81,0x81,
    0x81,0x81,0x81,0x81,0x81,0x81,0xFF,0xFF,
    // Tile 2: Simple Character/Hero Sprite
    0x3C,0x3C,0x42,0x42,0xA5,0xA5,0x81,0x81,
    0xA5,0xA5,0x42,0x42,0x3C,0x3C,0x18,0x18
};

// 20x18 background room (1 = Wall, 0 = Walkable floor)
const uint8_t room_map[18 * 20] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
    1,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
    1,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

uint8_t is_solid(uint8_t x, uint8_t y) {
    // Hardware sprite coordinates have an offset of (8, 16) relative to screen (0, 0)
    uint8_t tile_x = (x - 8) >> 3;
    uint8_t tile_y = (y - 16) >> 3;
    
    if (tile_x >= 20 || tile_y >= 18) return 1;
    return room_map[tile_y * 20 + tile_x] == 1;
}

void main(void) {
    uint8_t player_x = 80;
    uint8_t player_y = 72;

    // Load background tiles (0 & 1) and sprite tiles (2)
    set_bkg_data(0, 2, tile_data);
    set_bkg_tiles(0, 0, 20, 18, room_map);

    set_sprite_data(0, 1, &tile_data[32]); // Load hero tile into sprite memory
    set_sprite_tile(0, 0);                 // Sprite index 0 uses tile 0 from sprite data
    move_sprite(0, player_x, player_y);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while (1) {
        uint8_t keys = joypad();
        uint8_t next_x = player_x;
        uint8_t next_y = player_y;

        if (keys & J_UP)    next_y--;
        if (keys & J_DOWN)  next_y++;
        if (keys & J_LEFT)  next_x--;
        if (keys & J_RIGHT) next_x++;

        // Basic bounding box check (center point check)
        if (!is_solid(next_x, next_y)) {
            player_x = next_x;
            player_y = next_y;
            move_sprite(0, player_x, player_y);
        }

        // Wait for VBlank interrupt to sync at 60 FPS
        wait_vbl_done();
    }
}
