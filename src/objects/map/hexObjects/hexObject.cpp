#include "hexObject.hpp"

HexObject::HexObject()
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

void HexObject::applyWeapon(Weapon * weapon)
{
    std::cout << "in HEXOBJECT APPLYWEAPON" << std::endl;
}