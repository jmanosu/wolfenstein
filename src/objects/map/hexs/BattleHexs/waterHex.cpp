#include "waterHex.hpp"

#include "graphics/textureCache.hpp"

WaterHex::WaterHex() : BattleHex()
{
    TextureCache * textureCache = TextureCache::instance();

    setBorderTexture(textureCache->generateTexture("HighlightHex0"), (Direction)0);
    setBorderTexture(textureCache->generateTexture("HighlightHex1"), (Direction)1);
    setBorderTexture(textureCache->generateTexture("HighlightHex2"), (Direction)2);
    setBorderTexture(textureCache->generateTexture("HighlightHex3"), (Direction)3);
    setBorderTexture(textureCache->generateTexture("HighlightHex4"), (Direction)4);
    setBorderTexture(textureCache->generateTexture("HighlightHex5"), (Direction)5);

    setHexOverlayTexture(textureCache->generateTexture("HexOverlay"));

    _waterHexTexture = textureCache->generateAnimatedTexture("OceanHexAnimated");
    setHexTexture(_waterHexTexture);

    setSkirtTexture(textureCache->generateTexture("OceanSkirtHex"));

    mWidth = 43;
    mHeight = 33;
    mPeakHeight = 13;
}

WaterHex::~WaterHex()
{

}

void WaterHex::update()
{
    BattleHex::update();

    _waterHexTexture->update();
}