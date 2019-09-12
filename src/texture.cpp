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

void Texture::render(int x, int y, int width, int height)
{
    SDL_Rect texr; texr.x = x; texr.y = y; texr.w = width; texr.h = height; 
    mGraphics->drawTexture(mTexture, texr);
}