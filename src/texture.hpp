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

class Texture{
    public:
        Texture(std::string path);
        ~Texture();
        void render(int, int, int, int);
    private:
        SDL_Texture * mTexture;
        Graphics * mGraphics;


};

#endif