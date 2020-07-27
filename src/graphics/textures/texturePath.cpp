#include "texturePath.hpp"

TexturePath::TexturePath() :
    mPath(nullptr)
{

}

TexturePath::~TexturePath()
{
    delete mPath;
}

void TexturePath::render()
{
    mPath->render(&(mTexture), 40);
}

void TexturePath::setTexture(const Texture & texture)
{
    mTexture = texture;
}

void TexturePath::setPath(Path * path)
{
    mPath = path;
    mPath->parent(this);
}

void TexturePath::setEnd(GVector end)
{
    mPath->setEnd(end);
}

void TexturePath::setStart(GVector start)
{
    mPath->setStart(start);
}