#include "battleHex.hpp"

BattleHex::BattleHex() : PixelHex()
{

}

BattleHex::BattleHex(const BattleHex & hex) : PixelHex(hex)
{

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
  if (mHexObject != nullptr) {
    mHexObject->applyWeapon(weapon);
  }
}

void BattleHex::update()
{
    PixelHex<BattleHex>::update();

    if (mHovered == true) {
        mRenderBorders = true;
    } else {
        mRenderBorders = false;
    }
}
