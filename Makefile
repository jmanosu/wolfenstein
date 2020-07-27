CC = g++
LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
FLAGS = `sdl2-config --cflags`
FILES = \
./src/gameplay/battle/battle.cpp \
./src/gameplay/input/inputManager.cpp \
./src/gameplay/players/player.cpp \
./src/gameplay/screens/screen.cpp \
./src/gameplay/screens/screenManager.cpp \
./src/gameplay/screens/tempScreen.cpp \
./src/gameplay/timer/timer.cpp \
./src/gameplay/game.cpp \
./src/geometry/boundingBox.cpp \
./src/geometry/cubeCoord.cpp \
./src/geometry/line.cpp \
./src/geometry/path.cpp \
./src/graphics/textures/animatedTexture.cpp \
./src/graphics/textures/texturePath.cpp \
./src/graphics/textures/texture.cpp \
./src/graphics/assetManager.cpp \
./src/graphics/graphics.cpp \
./src/graphics/graphicUtils.cpp \
./src/graphics/textureCache.cpp \
./src/objects/map/hexEffects/hexEffect.cpp \
./src/objects/map/hexObjects/units/mech.cpp \
./src/objects/map/hexObjects/units/unit.cpp \
./src/objects/map/hexObjects/hexObject.cpp \
./src/objects/map/hexs/battleHex.cpp \
./src/objects/map/hexs/hexCollection.cpp \
./src/objects/map/weapons/weapon.cpp \
./src/objects/map/battleLocation.cpp \
./src/objects/map/battleMap.cpp \
./src/objects/map/mapUtils.cpp \
./src/objects/widgets/button.cpp \
./src/objects/widgets/widget.cpp \
./src/objects/gameEntity.cpp \
./src/objects/interactableEntity.cpp \
./src/utils/idGenerator.cpp \
./src/utils/jsonUtils.cpp \
./src/main.cpp


build: $(FILES)
	$(CC) -g -I ./src $(FILES) $(FLAGS) $(LIBS)