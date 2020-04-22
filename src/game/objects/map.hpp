/*
File: map.hpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header file for map. Map has a 3 dimensional array of wall objects
  called floors. This allows for multipule levels.

*/
#ifndef Map_hpp
#define Map_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <list>
#include <tuple>

#include "game/player/player.hpp"
#include "game/objects/gameEntity.hpp"
#include "game/objects/hexs/hex.hpp"
#include "game/utils/cubeCoord.hpp"
#include "misc/constants.hpp"
#include "managers/inputManager.hpp"
#include "graphics/animatedTexture.hpp"
#include "game/objects/weapon.hpp"


class Map : public GameEntity{
  public:
    Map();
    ~Map();

    void init();

    void render();
    void update();

    void handleClick(SDL_Event event);
    void initMapNeighbors();
    void loadMap(std::vector<std::vector<int>>, std::vector<Hex *>);

    void addHex(CubeCoord, Hex *);
    Hex * getHex(CubeCoord);

    void addHexObject(CubeCoord, HexObject *);
    HexObject * getHexObject(CubeCoord);
    HexObject * getHexObject(ID);

    void moveHexObject(CubeCoord, ID);

    Hex * getSelectedHex();
    Hex * getHoveredHex();
    Hex * getClickedHex();

    void applyWeapon(Weapon *, CubeCoord, CubeCoord);

  private:
    int boundX, boundY;
    int radius;

    std::map<CubeCoord, Hex *> mHexs;

    std::map<ID, HexObject *> mHexObjects;

    Hex * mSelectedHex;
    Hex * mHoveredHex;
    Hex * mClickedHex;
};

#endif