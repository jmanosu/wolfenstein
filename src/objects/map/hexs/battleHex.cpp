#include "battleHex.hpp"

BattleHex::BattleHex() : PixelHex()
{
  mFocusColor = { .r = 0, .g = 255, .b = 255, .a = 255};
  mHighlightColor = { .r = 0, .g = 255, .b = 0, .a =255};
  mHighlight = false;
}

BattleHex::BattleHex(const BattleHex & hex) : PixelHex(hex)
{
  mFocusColor = { .r = 0, .g = 255, .b = 255, .a = 255};
  mHighlightColor = { .r = 0, .g = 255, .b = 0, .a =255};
  mHighlight = false;
}


BattleHex::~BattleHex()
{
  
}

BattleHex * BattleHex::clone()
{
    return new BattleHex(*(this));
}

void BattleHex::applyWeapon(Weapon * weapon)
{
  
}

void BattleHex::update()
{
    PixelHex<BattleHex>::update();

    if (mHovered == true) {
      setBorderColor(mFocusColor);
      setHexOverlayColor(mFocusColor.r, mFocusColor.g, mFocusColor.b, 50);
      setRenderOverride(true);
      setRenderBorder(true);
      setRenderOverlay(true);
    } else {
        if (mHighlight) {
          setBorderColor(mHighlightColor);
          setHexOverlayColor(mHighlightColor.r, mHighlightColor.g, mHighlightColor.b, 50);
        }
      setRenderOverride(false);
    }
}

void BattleHex::setHighlight(bool highlight)
{
  mHighlight = highlight;
  if (highlight) {
    setPixelMode(PixelMode::GroupHighlight);
  } else {
    setPixelMode(PixelMode::Standard);
  }
}