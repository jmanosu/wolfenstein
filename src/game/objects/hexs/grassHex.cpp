#include  "grassHex.hpp"

GrassHex::GrassHex() : Hex()
{
    Texture hexTexture("hexTextures/grassHex.png", 0, 20, 29, 38);
    setHexTexture(hexTexture);

    Texture skirtTexture("hexTextures/grassHex.png", 29, 0, 29, 80);
    setHexSkirtTexture(skirtTexture);

    setHexDimensions(29, 38, 11);
}

GrassHex::~GrassHex()
{

}