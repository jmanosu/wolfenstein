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

#include "graphics.hpp"

class assetManager{
    public:
        static assetManager * instance();
        static void release();
        SDL_Texture * getTexture(std::string);

    private:
        assetManager();
        ~assetManager();

        std::map<std::string, SDL_Texture *> mTextures;
        static assetManager * sInstance;
};


#endif