CC = lcc
CFLAGS = -Wa-l -Wl-m -Wl-j
TARGET = build/game.gb
SRCS = src/main.c

GAMEBOY_CORE ?= /usr/lib64/libretro/mgba_libretro.so
EMULATOR = retroarch -L $(GAMEBOY_CORE)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS) | build 
	$(CC) $(CFLAGS) -o $@ $<

run: $(TARGET)
	$(EMULATOR) $(TARGET)

build: 
	mkdir -p build
