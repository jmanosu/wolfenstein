/*
File: hex.hpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header function for Hex
*/

#ifndef HEX_HPP
#define HEX_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <tuple>
#include <cmath>

#include "utils/constants.hpp"

#include "graphics/textures/texture.hpp"

#include "objects/gameEntity.hpp"
#include "objects/map/hexObjects/hexObject.hpp"
#include "objects/map/weapons/weapon.hpp"

#include "geometry/cubeCoord.hpp"

#include "gameplay/input/inputManager.hpp"

enum Orientation {
  vertical = 0,
  horizontal = 1
};

class Hex : public GameEntity{
  public:

    Hex();
    Hex(const Hex &hexR);
    ~Hex();

    Hex & operator = (Hex const &obj);

    virtual Hex * clone();

    void setDimensions(Orientation orientation, int width, int height, int peakHeight, int level);

    void setLocation(CubeCoord location);

    bool checkCollision(int, int);
    
    void addNeighbor(Hex *, Direction);

    void update();

    int getHighlighted() { return mHighlighted; }
    void setHighlighted(bool);
    void setLevel(int level) { mLevel = level; }

    void setHexObject(HexObject * hexObject);
    void releaseHexObject();
    HexObject * getHexObject();

    //game interaction
    virtual void applyWeapon(Weapon *);

    Orientation getOrientation() { return mOrientation; }

    CubeCoord getLocation() { return mLocation; }

    int getWidth()      { return mWidth;  }
    int getHeight()     { return mHeight; }
    int getPeakHeight() { return mPeakHeight; }
    int getLevel()      { return mLevel;  }

  protected:

    Orientation mOrientation;

    CubeCoord mLocation;

    std::vector<Hex *> mNeighbors;

    int mHeight, mWidth, mPeakHeight, mLevel;

    bool mHighlighted;

    HexObject * mHexObject;
};

#endif
