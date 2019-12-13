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
        Texture(std::string text, std::string fontPath, int size, SDL_Color color = {.r = 0, .g = 0, .b = 0, .a = 0});
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