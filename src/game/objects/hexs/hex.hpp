/*
File: hex.hpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header function for Hex
*/

#ifndef hex_hpp
#define hex_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <tuple>
#include <cmath>
#include "misc/constants.hpp"
#include "graphics/texture.hpp"
#include "graphics/hexTexture.hpp"
#include "game/objects/gameEntity.hpp"
#include "game/objects/hexObject.hpp"
#include "game/utils/cubeCoord.hpp"
#include "managers/inputManager.hpp"

class Hex : public GameEntity{
  public:
    Hex();
    Hex(const Hex &hexR);
    ~Hex();


    void setLocation(CubeCoord location, int height = 0);

    void setHexDimensions(int, int, int);

    void setHexTexture(Texture);
    void setHexSkirtTexture(Texture);
    
    void draw();
    bool checkCollision(int, int);
    
    int getX() { return mLocation.getX(); }
    int getY() { return mLocation.getY(); }
    int getZ() { return mLocation.getZ(); }
    
    void addNeighbor(Hex *, Direction);
    void update();

    void setHighlighted(bool);

    Hex & operator = (Hex const &obj);
  private:
    CubeCoord mLocation;

    Texture * hexTextureHighlight;
    Texture * mHexTexture;
    Texture * mHexSkirtTexture;

    std::vector<Hex *> mNeighbors;

    int mHeight, mWidth, mPeakHeight;

    bool mHighlighted;

    HexObject * mHexObject;
};

#endif
