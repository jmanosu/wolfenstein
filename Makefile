CC = g++
LIBS = `sdl2-config --cflags --libs` -lSDL2_image

build: ./src/main.cpp ./src/game.cpp ./src/map.cpp ./src/hex.cpp ./src/player.cpp ./src/graphics.cpp ./src/assetManager.cpp ./src/texture.cpp
	$(CC) ./src/main.cpp ./src/game.cpp ./src/map.cpp ./src/hex.cpp ./src/player.cpp ./src/graphics.cpp ./src/assetManager.cpp ./src/texture.cpp $(LIBS)