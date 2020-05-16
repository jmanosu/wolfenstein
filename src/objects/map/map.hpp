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

#include "objects/gameEntity.hpp"
#include "objects/map/hexGrid.hpp"
#include "objects/map/hexs/hex.hpp"
#include "objects/map/hexObjects/hexObject.hpp"
#include "objects/map/weapons/weapon.hpp"

#include "geometry/cubeCoord.hpp"

#include "utils/constants.hpp"

#include "gameplay/input/inputManager.hpp"

#include "graphics/textures/animatedTexture.hpp"



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

  protected:
    int boundX, boundY;
    int radius;

    std::map<CubeCoord, Hex *> mHexs;

    std::map<ID, HexObject *> mHexObjects;

    Hex * mSelectedHex;
    Hex * mHoveredHex;
    Hex * mClickedHex;

    HexGrid<Hex *> mHexGrid;
};

#endif