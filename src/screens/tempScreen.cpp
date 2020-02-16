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


  mMap = new Map();

  std::vector<Hex *> bind;

  bind.push_back(new LandHex(43, 33, 13, 0, "GrassHex", ""));
  bind.push_back(new LandHex(43, 33, 13, 0, "TreeHex", ""));
  bind.push_back(new LandHex(43, 33, 13, 0, "DesertHex", ""));
  bind.push_back(new LandHex(43, 33, 13, 0, "GrassHex", ""));
  bind.push_back(new LandHex(43, 33, 13, 0, "WaterHex", ""));

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