CC = g++
LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
FLAGS = `sdl2-config --cflags`
FILES = ./src/main.cpp \
./src/game/gameplay/battle.cpp \
./src/game/game.cpp \
./src/game/objects/gameEntity.cpp \
./src/game/objects/map.cpp \
./src/game/objects/hexObject.cpp \
./src/game/objects/weapon.cpp \
./src/game/objects/hexs/hex.cpp \
./src/game/objects/hexs/landHex.cpp \
./src/game/objects/units/unit.cpp \
./src/game/objects/units/mech.cpp \
./src/game/utils/hexGrid.cpp \
./src/game/utils/idGenerator.cpp \
./src/game/utils/cubeCoord.cpp \
./src/game/player/player.cpp \
./src/graphics/graphics.cpp \
./src/graphics/texture.cpp \
./src/graphics/animatedTexture.cpp \
./src/graphics/textureCache.cpp \
./src/managers/assetManager.cpp \
./src/managers/inputManager.cpp \
./src/managers/screenManager.cpp \
./src/misc/timer.cpp \
./src/screens/screen.cpp \
./src/screens/tempScreen.cpp \

build: $(FILES)
	$(CC) -I ./src $(FILES) $(FLAGS) $(LIBS)