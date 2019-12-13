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
#include <SDL2/SDL_ttf.h>
#include "gamingVector.hpp"

class Graphics{
    public:
        static Graphics * instance();
        static void release();
        static bool initalized();

        void render();
        void clear();

        SDL_Renderer * getRenderer();
        SDL_Texture * loadTexture(std::string);
        SDL_Texture * createTextTexture(TTF_Font * font, std::string text, SDL_Color color = {.r = 0, .g = 0, .b = 0, .a = 0});

        void printError();

        void drawTexture(SDL_Texture *, SDL_Rect *, SDL_Rect *);
        void drawLine(int, int, int, int);
        void drawPoint(int, int);
        void drawPoint(GVector);
        
        void setColor(int, int, int, double);

    public:
        static const int screenHeight = 1000;
        static const int screenWidth  = 1400;
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