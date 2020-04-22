#include "tempScreen.hpp"
#include "game/objects/hexs/landHex.hpp"
#include "graphics/textureCache.hpp"


TempScreen::TempScreen()
{
  mBattle = new Battle();
}

TempScreen::~TempScreen()
{
  delete mBattle;
}

void TempScreen::render()
{
  mBattle->render();
}

void TempScreen::update()
{
  mBattle->update();
}

void TempScreen::load()
{

}