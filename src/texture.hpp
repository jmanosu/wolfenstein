/*
File: texture.hpp
Author: Jared Tence
Last Edit: 9/9/2019

Description: Player object header file
*/

#ifndef texture_hpp
#define texture_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "assetManager.hpp"
#include "gameEntity.hpp"

class Texture : public GameEntity{
    public:
        Texture(std::string path);
        Texture(std::string path, int x, int y, int width, int height);
        ~Texture();

        int getHeight() { return mHeight; }
        int getWidth() { return mWidth; }
    
        void update();
        void render();
        void render(int, int, int, int);
    protected:
        SDL_Texture * mTexture;
        Graphics * mGraphics;
        int mHeight, mWidth;
        SDL_Rect mRenderRect, mClipRect;
        bool mClipped;


};

#endif