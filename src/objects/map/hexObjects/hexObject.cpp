#include "hexObject.hpp"

HexObject::HexObject() :
    _placed(false)
{

}

HexObject::~HexObject()
{
    delete mHexObjectTexture;
}

void HexObject::render()
{
    if (mHexObjectTexture != nullptr) {
        mHexObjectTexture->render();
    }
}

void HexObject::update()
{

}

void HexObject::setLocation(CubeCoord location)
{
    mLocation = location;
}

CubeCoord HexObject::getLocation()
{
    return mLocation;
}

void HexObject::setPlaced(bool placed)
{
    _placed = placed;
}

bool HexObject::getPlaced()
{
    return _placed;
}

void HexObject::applyWeapon(Weapon * weapon)
{
    std::cout << "in HEXOBJECT APPLYWEAPON" << std::endl;
}