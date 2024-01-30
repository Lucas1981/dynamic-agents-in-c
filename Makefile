CC=gcc

# Compiler warning flags
WARN_FLAGS=-Wall -Wextra -Werror -Wshadow -Wconversion -Wstrict-prototypes -pedantic

# Use sdl2-config to set the compiler and linker flags for SDL2
CFLAGS=$(shell sdl2-config --cflags) $(WARN_FLAGS)
LDFLAGS=$(shell sdl2-config --libs)

# Add SDL2_image flags
CFLAGS+= $(shell pkg-config --cflags SDL2_image)
LDFLAGS+= $(shell pkg-config --libs SDL2_image)

# Add SDL2_mixer flags
CFLAGS+= $(shell pkg-config --cflags SDL2_mixer)
LDFLAGS+= $(shell pkg-config --libs SDL2_mixer)

# Add SDL2_ttf flags
CFLAGS+= $(shell pkg-config --cflags SDL2_ttf)
LDFLAGS+= $(shell pkg-config --libs SDL2_ttf)

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
TARGET=game

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f src/*.o $(TARGET)

cleanobj:
	rm -f src/*.o

.PHONY: clean
