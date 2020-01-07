#include "oceanHex.hpp"

OceanHex::OceanHex() : Hex()
{
    Texture oceanTexture("hexTextures/oceanHex.png", 0, 20, 29, 38);
    setHexTexture(oceanTexture);

    setHexDimensions(29, 38, 11);

    GVector currentPos = pos(local);

    currentPos.y = currentPos.y + scale().y * 3;

//    pos(currentPos);
}

OceanHex::~OceanHex()
{

}