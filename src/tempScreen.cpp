#include "tempScreen.hpp"

TempScreen::TempScreen()
{
    mMap = new Map();
}

TempScreen::~TempScreen()
{
    delete mMap;
}

void TempScreen::render()
{
    mMap->render();
}

void TempScreen::update()
{
    mMap->update();
}