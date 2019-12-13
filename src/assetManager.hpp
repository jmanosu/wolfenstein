/*
File: assetManager.hp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header function for assetManager.hpp
*/
#ifndef ASSETMANAGER
#define ASSETMANAGER

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "graphics.hpp"

class assetManager{
    public:
        static assetManager * instance();
        static void release();
        SDL_Texture * getTexture(std::string);
        SDL_Texture * getTextTexture(std::string text, std::string fileName, int size, SDL_Color color = {.r = 0, .g = 0, .b = 0, .a = 0});

    private:
        assetManager();
        ~assetManager();

        TTF_Font * getFont(std::string, int);

        std::map<std::string, SDL_Texture *> mTextures;
        std::map<std::string, SDL_Texture *> mTextTextures;
        std::map<std::string, TTF_Font *> mFonts;
        static assetManager * sInstance;
};

#endif