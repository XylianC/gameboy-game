#include <gb/gb.h>
#include <stdint.h>
#include "hud.h"

unsigned char hud_buffer[HUD_WIDTH * HUD_HEIGHT];

uint8_t charToTile(char c) {
    if (c >= '0' && c <= '9') {
        return (uint8_t)(c - '0' + 1);    // '0' -> 0x01 ... '9' -> 0x0A
    }
    if (c >= 'a' && c <= 'z') {
        return (uint8_t)(c - 'a' + 0x0B); // 'a' -> 0x0B ... 'z' -> 0x24
    }
    if (c >= 'A' && c <= 'Z') {
        return (uint8_t)(c - 'A' + 0x0B); // uppercase support
    }
    return 0x00; // Space / Blank tile ('_')
}

static void writeHudText(uint8_t x, uint8_t y, const char *str) {
    uint8_t i = 0;
    uint8_t offset = (y * HUD_WIDTH) + x;

    while (str[i] != '\0' && (x + i) < HUD_WIDTH) {
        hud_buffer[offset + i] = charToTile(str[i]);
        i++;
    }
}

void hud_update_level(uint8_t level) {
    // Write 2-digit number at (X: 9, Y: 1)
    hud_buffer[(1 * HUD_WIDTH) + 9]  = charToTile((level / 10) + '0');
    hud_buffer[(1 * HUD_WIDTH) + 10] = charToTile((level % 10) + '0');

    // Push updated level tiles directly to VRAM
    set_win_tiles(9, 1, 2, 1, &hud_buffer[(1 * HUD_WIDTH) + 9]);
}

void hud_update_name(const char *playerName) {
    writeHudText(0, 1, playerName);
    set_win_tiles(0, 1, 6, 1, &hud_buffer[(1 * HUD_WIDTH) + 0]);
}

void initHud(const char *playerName, uint8_t initialLevel) {
    uint8_t i;
    // Clear buffer to blank tiles (0x00)
    for (i = 0; i < (HUD_WIDTH * HUD_HEIGHT); i++) {
        hud_buffer[i] = 0x00;
    }

    // Top row labels
    writeHudText(0, 0, "player");
    writeHudText(8, 0, "lvl");

    // Bottom row dynamic values
    writeHudText(0, 1, playerName);
    
    // Set initial level digits in buffer
    hud_buffer[(1 * HUD_WIDTH) + 9]  = charToTile((initialLevel / 10) + '0');
    hud_buffer[(1 * HUD_WIDTH) + 10] = charToTile((initialLevel % 10) + '0');

    // Transfer complete 12x2 block to Window layer VRAM
    set_win_tiles(0, 0, HUD_WIDTH, HUD_HEIGHT, hud_buffer);

    // Position the window layer at bottom of screen
    move_win(6, 128);
}
