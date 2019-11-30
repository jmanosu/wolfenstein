CC = g++
LIBS = `sdl2-config --cflags --libs` -lSDL2_image
FILES = ./src/main.cpp \
./src/game.cpp \
./src/map.cpp \
./src/player.cpp \
./src/graphics.cpp \
./src/assetManager.cpp \
./src/texture.cpp \
./src/hexTexture.cpp \
./src/timer.cpp \
./src/gameEntity.cpp \
./src/inputManager.cpp \
./src/cornerSpace.cpp \
./src/hex.cpp \
./src/cubeCoord.cpp

build: $(FILES)
	$(CC) $(FILES) $(LIBS)