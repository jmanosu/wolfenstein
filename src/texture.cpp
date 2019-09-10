#include "texture.hpp"

Texture::Texture(std::string path)
{
    mGraphics = Graphics::instance();
    mTexture  = assetManager::instance()->getTexture(path);
}

Texture::~Texture()
{
    mGraphics = nullptr;
    mTexture  = nullptr;
}

void Texture::render()
{
    mGraphics->drawTexture(mTexture);
}