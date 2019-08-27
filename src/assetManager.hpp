/*
File: assetManager.hp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header function for assetManager.hpp
*/

#include <iostream>
#include <map>
#include <SDL2/SDL.h>

#ifndef ASSETMANAGER
#define ASSETMANAGER

class assetManager{
    public:
        static assetManager * instance();
        static SDL_Texture * getTexture(std::string);
        static void loadTexture(std::string);
        static void release();

    private:
        assetManager();
        ~assetManager();

        static std::map<std::string, SDL_Texture *> mTextures;
        static assetManager * sInstance;
};


#endif