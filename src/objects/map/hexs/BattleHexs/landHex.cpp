#include "landHex.hpp"

#include "graphics/textureCache.hpp"

/*
            "HighlightNorthWest" : "HighlightHex1",
            "NorthHighlight" : "HighlightHex2",
            "NorthEastHighlight" : "HighlightHex3",
            "SouthEastHighlight" : "HighlightHex4",
            "SouthHighlight" : "HighlightHex5",
            "SouthWestHighlight" : "HighlightHex6",
            "PathTextures" : [
                "pathDirection1",
                "pathDirection2",
                "pathDirection3",
                "pathDirection4",
                "pathDirection5",
                "pathDirection6"
            ],
            "TileTexture" : "DesertHex",
            "OverlayTexture" : "HexOverlay",
            "SkirtTexture" : "GroundSkirtHex",
*/

LandHex::LandHex() : BattleHex()
{
    TextureCache * textureCache = TextureCache::instance();


    _grassHexTexture = textureCache->generateTexture("GrassHex");
    _desertHexTexture = textureCache->generateTexture("DesertHex");
    _snowHexTexture = textureCache->generateTexture("SnowHex");

    setBorderTexture(textureCache->generateTexture("HighlightHex0"), (Direction)0);
    setBorderTexture(textureCache->generateTexture("HighlightHex1"), (Direction)1);
    setBorderTexture(textureCache->generateTexture("HighlightHex2"), (Direction)2);
    setBorderTexture(textureCache->generateTexture("HighlightHex3"), (Direction)3);
    setBorderTexture(textureCache->generateTexture("HighlightHex4"), (Direction)4);
    setBorderTexture(textureCache->generateTexture("HighlightHex5"), (Direction)5);

    setHexOverlayTexture(textureCache->generateTexture("HexOverlay"));
    setSkirtTexture(textureCache->generateTexture("GroundSkirtHex"));

    setHexTexture(_grassHexTexture);

    mWidth = 43;
    mHeight = 33;
    mPeakHeight = 13;
}

LandHex::~LandHex()
{
    delete _grassHexTexture;
    delete _snowHexTexture;
    delete _desertHexTexture;
}

void LandHex::setType(LandHexType type)
{
    switch (type)
    {
        case grass:
            {
                setHexTexture(_grassHexTexture);
            }
            break;
        case desert:
            {
                setHexTexture(_desertHexTexture);
            }
            break;
        case snow:
            {
                setHexTexture(_snowHexTexture);
            }
            break;
        default:
            break;
    }

    _type = type;
}