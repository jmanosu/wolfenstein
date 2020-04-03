#include "tempScreen.hpp"
#include "game/objects/hexs/landHex.hpp"
#include "graphics/textureCache.hpp"


TempScreen::TempScreen()
{

  TextureCache * textureCache = TextureCache::instance();

  textureCache->loadFile("textureFiles/test.json");


  mMap = new Map();

  std::vector<Hex *> bind;

  Hex templateHex;

  templateHex.setHighlightTexture(*(textureCache->getTexture("HighlightHex1")), NorthWest);
  templateHex.setHighlightTexture(*(textureCache->getTexture("HighlightHex2")), North);
  templateHex.setHighlightTexture(*(textureCache->getTexture("HighlightHex3")), NorthEast);
  templateHex.setHighlightTexture(*(textureCache->getTexture("HighlightHex4")), SouthEast);
  templateHex.setHighlightTexture(*(textureCache->getTexture("HighlightHex5")), South);
  templateHex.setHighlightTexture(*(textureCache->getTexture("HighlightHex6")), SouthWest);

  templateHex.setDimensions(horizontal, 43, 33, 13, 0);

  bind.push_back(new LandHex(templateHex, "GrassHex", "GroundSkirtHex"));
  bind.push_back(new LandHex(templateHex, "TreeHex", "GroundSkirtHex"));
  bind.push_back(new LandHex(templateHex, "DesertHex", "DesertSkirtHex"));
  bind.push_back(new LandHex(templateHex, "SnowHex", "GroundSkirtHex"));
  bind.push_back(new LandHex(templateHex, "WaterHex", "OceanSkirtHex"));
  bind.push_back(new LandHex(templateHex, "SnowForestHex", "GroundSkirtHex"));


  bind.at(1)->setLevel(4);
  bind.at(4)->setLevel(-4);
  
  std::vector<std::vector<int>> map {
    { 4,  4,  4,  0,  4,  4,  4},
    { 4,  4,  0,  2,  1,  4,  4},
    { 4,  0,  2,  2,  1,  0,  4},
    { 0,  4,  4,  0,  3,  3,  0},
    { 4,  4,  0,  3,  5,  0,  4},
    { 4,  4,  0,  0,  0,  4,  4},
    { 4,  4,  4,  0,  4,  4,  4}
  };


  mMap->loadMap(map, bind);
}

TempScreen::~TempScreen()
{
  delete mMap;
}

void TempScreen::render()
{
  mMap->render();
  SDL_SetRenderDrawColor(Graphics::instance()->getRenderer(), 5, 42, 74, 255);
}

void TempScreen::update()
{
  mMap->update();
}

void TempScreen::load()
{

}