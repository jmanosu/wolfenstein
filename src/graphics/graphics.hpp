/*
File: graphics.hpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header function for graphics.hpp
*/

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "geometry/gamingVector.hpp"

struct RGBA {
    int r = 255;
    int g = 255;
    int b = 255;
    int a = 255;
};

class Graphics{
    public:
        static Graphics * instance();
        static void release();
        static bool initalized();

        void render();
        void clear();

        SDL_Renderer * getRenderer();
        SDL_Window * getWindow();

        SDL_Texture * loadTexture(std::string);
        SDL_Texture * createTextTexture(TTF_Font * font, std::string text, SDL_Color color = {.r = 0, .g = 0, .b = 0, .a = 0});

        void printError();

        void drawTexture(SDL_Texture *, SDL_Rect *, SDL_Rect *);
        void drawLine(int, int, int, int);
        void drawPoint(int, int);
        void drawPoint(GVector);

        void drawRectangle(int, int, int, int, bool);
        
        void setColor(int, int, int, double);
        void setTextureColor(SDL_Texture *, int red = 255, int green = 255, int blue = 255, int alpha = 255);

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