#include "boundingBox.hpp"

BoundingBox::BoundingBox() :
    mWidth(0),
    mHeight(0)
{

}

BoundingBox::~BoundingBox()
{

}

int BoundingBox::getWidth()
{
    return mWidth;
}

void BoundingBox::setWidth(int width)
{
    mWidth = width;
}

int BoundingBox::getHeight()
{
    return mHeight;
}

void BoundingBox::setHeight(int height)
{
    mHeight = height;
}

bool BoundingBox::collision(int x, int y)
{
    GVector vector = pos(world);

    if (x > (vector.x - mWidth / 2) && x < (vector.x + mWidth / 2)) {
        if (x > (vector.y - mHeight / 2) && y < (vector.y + mHeight / 2)) {
            return true;
        }
    }

    return false;
}