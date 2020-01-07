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

class HexTexture : public Texture {
    public:
        HexTexture() {}
        HexTexture(std::string path, int, int, int);
        ~HexTexture();
        void renderHex();
        void renderLeftCascade();
        void renderRightCascade();
        void render();
        int getHexWidth() { return mHexWidth; }
        int getHexHeight() { return mHexHeight; }
        int getPeakHeight() { return mPeakHeight; }
    private:
        int mHexWidth, mHexHeight, mPeakHeight;

};

#endif