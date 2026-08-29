CC = lcc
CFLAGS = -Wa-l -Wl-m -Wl-j
TARGET = build/game.gb
SRCS = src/main.c

EMULATOR = sameboy 


.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS) | build 
	$(CC) $(CFLAGS) -o $@ $<

run: $(TARGET)
	$(EMULATOR) $(TARGET)

build: 
	mkdir -p build
