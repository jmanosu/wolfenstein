#include "landHex.hpp"
#include "graphics/textureCache.hpp"

LandHex::LandHex(std::string imageFile) : Hex()
{
    Texture landTexture(imageFile, 0, 0, 43, 85);
    setHexTexture(landTexture);

    Texture landSkirtTexture(imageFile, 43, 0, 43, 85);
    setSkirtTexture(landSkirtTexture);

    Texture landOutlineTexture(imageFile, 0,0,1,1);
    setOutlineTexture(landOutlineTexture);

    setDimensions(horizontal, 43, 33, 13, 0);

    mLevel = 0;
    mImageFile = imageFile;
}

LandHex::LandHex(int width, int height, int peakHeight, int level, std::string hexTexture, std::string skirtTexture)
{
    TextureCache * textureCache = TextureCache::instance();

    _setHexTexture(textureCache->getTexture(hexTexture));

    _setSkirtTexture(textureCache->getTexture(skirtTexture));

    setDimensions(horizontal, width, height, peakHeight, level);
}

LandHex::~LandHex()
{

}

Hex * LandHex::clone()
{
    LandHex * newLandHex = new LandHex(*(this));

    return newLandHex;
}