/*
File: hexTexture.hpp
Author: Jared Tence
Last Edit: 9/9/2019

Description: Player object header file
*/

#ifndef hexTexture_hpp
#define hexTexture_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include "texture.hpp"

class HexTexture : public Texture{
    public:
        HexTexture(std::string path, int, int, int);
        ~HexTexture();
        //void render(double, double, double);
        int getHexWidth() { return hexWidth; }
        int getHexHeight() { return hexHeight; }
        int getPeakHeight() { return peakHeight; }
    private:
        int hexWidth, hexHeight, peakHeight;

};

#endif