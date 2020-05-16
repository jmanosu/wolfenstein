/*
File: texture.hpp
Author: Jared Tence
Last Edit: 9/9/2019

Description: Player object header file
*/

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <SDL2/SDL.h>

#include "graphics/graphics.hpp"
#include "graphics/assetManager.hpp"

#include "objects/gameEntity.hpp"

class Texture : public GameEntity {
    public:
        Texture();
        Texture(std::string path);
        Texture(std::string path, int x, int y, int width, int height);
        Texture(std::string text, std::string fontPath, int size, SDL_Color color = {.r = 0, .g = 0, .b = 0, .a = 0});
        ~Texture();

        int getHeight() { return mHeight; }
        int getWidth() { return mWidth; }

        Texture clip(int x, int y, int width, int height);
    
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

namespace TextureUtils {
    void copy(const Texture * & source, Texture * & destination);
};

#endif