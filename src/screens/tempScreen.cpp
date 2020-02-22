#include "tempScreen.hpp"
#include "game/objects/hexs/landHex.hpp"
#include "graphics/textureCache.hpp"


TempScreen::TempScreen()
{

  TextureCache * textureCache = TextureCache::instance();

  textureCache->stashTexture("GrassHex", new Texture("hexFinalTextures/GrassHex.png", 0, 0, 43, 85));
  textureCache->stashTexture("TreeHex", new Texture("hexFinalTextures/TreeHex.png", 0, 0, 43, 85));
  textureCache->stashTexture("DesertHex", new Texture("hexFinalTextures/DesertHex.png", 0, 0, 43, 85));
  textureCache->stashTexture("WaterHex", new Texture("hexFinalTextures/WaterHex.png", 0, 0, 43, 85));
  textureCache->stashTexture("GroundSkirtHex", new Texture("hexFinalTextures/GrassHex.png", 43, 0, 43, 85));
  textureCache->stashTexture("OceanSkirtHex", new Texture("hexFinalTextures/WaterHex.png", 43, 0, 43, 85));
  textureCache->stashTexture("DesertSkirtHex", new Texture("hexFinalTextures/DesertHex.png", 43, 0, 43, 85));
  textureCache->stashTexture("HighlightHex1", new Texture("hexFinalTextures/HighlightTexture.png", 0, 0, 43, 85));
  textureCache->stashTexture("HighlightHex2", new Texture("hexFinalTextures/HighlightTexture.png", 43, 0, 43, 85));
  textureCache->stashTexture("HighlightHex3", new Texture("hexFinalTextures/HighlightTexture.png", 86, 0, 43, 85));
  textureCache->stashTexture("HighlightHex4", new Texture("hexFinalTextures/HighlightTexture.png", 129, 0, 43, 85));
  textureCache->stashTexture("HighlightHex5", new Texture("hexFinalTextures/HighlightTexture.png", 172, 0, 43, 85));
  textureCache->stashTexture("HighlightHex6", new Texture("hexFinalTextures/HighlightTexture.png", 215, 0, 43, 85));


  mMap = new Map();

  std::vector<Hex *> bind;

  Hex templateHex;

  templateHex._setHighlightTexture(textureCache->getTexture("HighlightHex1"), NorthWest);
  templateHex._setHighlightTexture(textureCache->getTexture("HighlightHex2"), North);
  templateHex._setHighlightTexture(textureCache->getTexture("HighlightHex3"), NorthEast);
  templateHex._setHighlightTexture(textureCache->getTexture("HighlightHex4"), SouthEast);
  templateHex._setHighlightTexture(textureCache->getTexture("HighlightHex5"), South);
  templateHex._setHighlightTexture(textureCache->getTexture("HighlightHex6"), SouthWest);

  templateHex.setDimensions(horizontal, 43, 33, 13, 0);

  bind.push_back(new LandHex(templateHex, "GrassHex", "GroundSkirtHex"));
  bind.push_back(new LandHex(templateHex, "TreeHex", "GroundSkirtHex"));
  bind.push_back(new LandHex(templateHex, "DesertHex", "DesertSkirtHex"));
  bind.push_back(new LandHex(templateHex, "GrassHex", "GroundSkirtHex"));
  bind.push_back(new LandHex(templateHex, "WaterHex", "OceanSkirtHex"));

  bind.at(1)->setLevel(4);
  bind.at(4)->setLevel(-4);

/*
  bind.push_back(new LandHex(43, 33, 13, 0, "GrassHex", "GroundSkirtHex", "HexHighlight"));
  bind.push_back(new LandHex(43, 33, 13, 4, "TreeHex", "GroundSkirtHex", "HexHighlight"));
  bind.push_back(new LandHex(43, 33, 13, 0, "DesertHex", "DesertSkirtHex", "HexHighlight"));
  bind.push_back(new LandHex(43, 33, 13, 0, "GrassHex", "GroundSkirtHex", "HexHighlight"));
  bind.push_back(new LandHex(43, 33, 13, -4, "WaterHex", "OceanSkirtHex", "HexHighlight"));
*/
  std::vector<std::vector<int>> map {
    { 4,  4,  4,  0,  4,  4,  4},
    { 4,  4,  0,  2,  1,  4,  4},
    { 4,  0,  2,  2,  1,  0,  4},
    { 0,  4,  4,  0,  3,  3,  0},
    { 4,  4,  0,  3,  0,  0,  4},
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