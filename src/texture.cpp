#include "texture.hpp"

Texture::Texture(std::string path)
{
    GameEntity();

    mGraphics = Graphics::instance();
    mTexture  = assetManager::instance()->getTexture(path);

    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);

    mRenderRect.w = mWidth;
    mRenderRect.h = mHeight;

    mClipRect.x = 0;
    mClipRect.y = 0;
    mClipRect.w = mWidth;
    mClipRect.h = mHeight;
}

Texture::Texture(std::string path, int x, int y, int width, int height)
{
    GameEntity();

    mGraphics = Graphics::instance();
    mTexture  = assetManager::instance()->getTexture(path);

    mClipped = true;

    mClipRect.x = x;
    mClipRect.y = y;
    mClipRect.w = width;
    mClipRect.h = height;
}

Texture::~Texture()
{
    mGraphics = nullptr;
    mTexture  = nullptr;
}

void Texture::render(int x, int y, int width, int height)
{
    SDL_Rect renderRect, clipRect;
    renderRect = {x, y, width, height}; 
    clipRect = {0, 0, width, height};
    mGraphics->drawTexture(mTexture, clipRect, renderRect);
}

void Texture::render()
{
    GVector::GVector pos = this->pos(world);
    GVector::GVector scaller = this->scale(world);

    mRenderRect.x = static_cast<int>(pos.x - 0.5f * mWidth/* * scaller.x*/);
    mRenderRect.y = static_cast<int>(pos.y - 0.5f * mHeight/* * scaller.y*/);

    mRenderRect.w = static_cast<int>(mWidth/* * scaller.x*/);
    mRenderRect.h = static_cast<int>(mHeight/* * scaller.y*/);

    mGraphics->drawTexture(mTexture, mClipRect, mRenderRect);
}

void Texture::update()
{

}