#ifndef LANDHEX
#define LANDHEX

#include "hex.hpp"
#include <iostream>

class LandHex : public Hex {
    public:
        LandHex(std::string imageFile);
        LandHex(Hex &, std::string hexTexture, std::string skirtTexture);
        LandHex(int width, int height, int peakHeight, int level, std::string hexTexture, std::string skirtTexture, std::string highlightTexture);
        ~LandHex();
        Hex * clone();
    protected:
        std::string mImageFile;
};

#endif