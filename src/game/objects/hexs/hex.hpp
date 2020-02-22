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

#include "game/objects/gameEntity.hpp"
#include "game/objects/hexObject.hpp"

#include "game/utils/cubeCoord.hpp"

#include "managers/inputManager.hpp"

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

    void _setHexTexture(const Texture *);
    void _setSkirtTexture(const Texture *);
    void _setOutlineTexture(const Texture *);
    void _setHighlightTexture(const Texture *, Direction);

    void setHexTexture(const Texture & hexTexture) { _setHexTexture(&(hexTexture)); }
    void setSkirtTexture(const Texture & skirtTexture) { _setSkirtTexture(&(skirtTexture)); }
    void setOutlineTexture(const Texture & outlineTexture) { _setOutlineTexture(&(outlineTexture)); }
    void setHighlightTexture(const Texture & highlightTexture, Direction direction) { _setHighlightTexture(&(highlightTexture), direction); } 

    Texture * _getHighlightTexture(int i);

    void renderHighlight(Direction);
    void renderHighlight();

    virtual void renderBackground();
    virtual void renderMidground();
    virtual void renderForground();

    void render();

    bool checkCollision(int, int);
    
    void addNeighbor(Hex *, Direction);

    void update();

    int getHighlighted() { return mHighlighted; }
    void setHighlighted(bool);
    void setLevel(int level) { mLevel = level; }

    void setHexObject(HexObject * hexObject);
    void releaseHexObject();

    //accessors
    int getX() { return mLocation.getX(); }
    int getY() { return mLocation.getY(); }
    int getZ() { return mLocation.getZ(); }

    Orientation getOrientation() { return mOrientation; }

    int getWidth()      { return mWidth;  }
    int getHeight()     { return mHeight; }
    int getPeakHeight() { return mPeakHeight; }
    int getLevel()      { return mLevel;  }

  protected:

    Orientation mOrientation;

    CubeCoord mLocation;

    //Hex Textures;
    Texture * mHexTexture;
    Texture * mSkirtTexture;
    Texture * mOutlineTexture;
    Texture * mHighlightTexture;

    std::vector<Texture *>  mHighlightTextures;

    std::vector<Hex *> mNeighbors;

    int mHeight, mWidth, mPeakHeight, mLevel;

    bool mHighlighted;

    HexObject * mHexObject;
};

#endif
