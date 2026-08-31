CC = lcc
CFLAGS = -Wa-l -Wl-m -Wl-j -Iinclude -Igen
TARGET = bin/game.gb
EMULATOR = WINEPREFIX=$(HOME)/.wine-gbdev wine $(HOME)/.wine-gbdev/drive_c/gbdev/bgb/bgb.exe
SRCS = $(wildcard src/*.c) \
			 $(wildcard src/*/*.c) \
			 $(wildcard gen/*.c) \
			 $(wildcard gen/*/*.c)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS) | build 
	$(CC) $(CFLAGS) -o $@ $(SRCS)

run: $(TARGET)
	$(EMULATOR) $(TARGET)

build: 
	mkdir -p bin
