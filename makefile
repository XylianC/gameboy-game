CC = lcc
CFLAGS = -Wa-l -Wl-m -Wl-j -Iinclude -Igen
TARGET = bin/game.gb
EMULATOR = sameboy 
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
