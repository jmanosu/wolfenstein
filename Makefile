CC = g++
LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
FLAGS = `sdl2-config --cflags`
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
./src/cubeCoord.cpp \
./src/animatedTexture.cpp \
./src/screen.cpp \
./src/screenManager.cpp \
./src/tempScreen.cpp

build: $(FILES)
	$(CC) $(FILES) $(FLAGS) $(LIBS)