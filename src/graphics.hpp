/*
File: graphics.hpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header function for graphics.hpp
*/

#ifndef GRAPHICS
#define GRAPHICS

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Graphics{
    public:
        static Graphics * instance();
        static void release();
        static bool initalized();

        void render();
        void clear();
        void drawTexture(SDL_Texture *, SDL_Rect &);
        SDL_Renderer * getRenderer();
        SDL_Texture * loadTexture(std::string);
        void printError();

    public:
        static const int screenHeight = 700;
        static const int screenWidth  = 700;
        static bool fullScreen;

    private:
        Graphics();
        ~Graphics();

        bool init();

    private:
        static Graphics * sInstance;
        static bool sInitalized;

        SDL_Window * mWindow;
        SDL_Texture * mTexture;
        SDL_Renderer * mRenderer;
};


#endif