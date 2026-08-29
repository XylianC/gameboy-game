Developping a game for the gameboy is much easier then I thought. 

The main c file is currently only a few lines and it is a top down working 1
room 8x8 map. 

Just using `lcc -Wa-l -Wl-m -Wl-j -o zelda_demo.gb main.c` compiles main.c into
a usable gameboy.gb file which can be read and played by any emulator.

This will definetly become a nice project
