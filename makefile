CC = lcc
TARGET = bin/game.gb
EMULATOR = WINEPREFIX=$(HOME)/.wine-gbdev wine $(HOME)/.wine-gbdev/drive_c/gbdev/bgb/bgb.exe

# Automatically find every subdirectory inside include/ and gen/ and add -I
INCLUDES = -Iinclude -Igen \
           $(shell find include gen src -type d -exec echo -I{} \;)

CFLAGS = -Wa-l -Wl-m -Wl-j $(INCLUDES)

SRCS = $(wildcard src/*.c) \
       $(wildcard src/*/*.c) \
       $(wildcard gen/*.c) \
       $(wildcard gen/*/*.c)

HDRS = $(wildcard include/*.h) \
       $(wildcard include/*/*.h) \
       $(wildcard gen/*.h) \
       $(wildcard gen/*/*.h)

.PHONY: all clean run build

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS) | build
	$(CC) $(CFLAGS) -o $@ $(SRCS)

build:
	mkdir -p $(dir $(TARGET))

run: $(TARGET)
	$(EMULATOR) $(TARGET)

clean:
	rm -rf bin *.o *.lst *.map *.sym *.noi *.ihx
