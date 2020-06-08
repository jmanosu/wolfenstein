#include "texturePath.hpp"

TexturePath::TexturePath() :
    mPath(nullptr),

    mDX(0),
    mLowerX(0),
    mUpperX(0)
{

}

TexturePath::~TexturePath()
{
    delete mPath;
}

void TexturePath::render()
{
    double x = mLowerX;

    while (x < mUpperX && mDX != 0) {
        double y = mPath->getOutput(x);

        GVector pos;

        pos.x = x;
        pos.y = y;

        mTexture.render(pos);

        x += mDX;
    }
}

void TexturePath::setTexture(const Texture & texture)
{
    mTexture = texture;
}

void TexturePath::setPath(Path * path)
{
    mPath = path;
}

void TexturePath::setDX(double dx)
{
    mDX = dx;
}

void TexturePath::setLowerX(double x)
{
    mLowerX = x;
}

void TexturePath::setUpperX(double x)
{
    mUpperX = x;
}