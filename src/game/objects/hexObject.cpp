#include "hexObject.hpp"

HexObject::HexObject()
{
    mHexObjectTexture = new Texture("hexObjects/Mech2.png");
    mHexObjectTexture->parent(this);
    this->pos(GVector(3,-7));
}

HexObject::~HexObject()
{
    delete mHexObjectTexture;
}

void HexObject::render()
{
    mHexObjectTexture->render();
}

void HexObject::update()
{

}