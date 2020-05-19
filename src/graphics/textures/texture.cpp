#include "texture.hpp"

Texture::Texture() : GameEntity()
{
    mGraphics = nullptr;
    mTexture = nullptr;

    mRed = 255;
    mGreen = 255;
    mBlue = 255;
    mAlpha = 255;
}

Texture::Texture(std::string path) : Texture()
{
    mGraphics = Graphics::instance();
    mTexture  = assetManager::instance()->getTexture(path);

    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);

    mClipRect.x = 0;
    mClipRect.y = 0;
    mClipRect.w = mWidth;
    mClipRect.h = mHeight;
}

Texture::Texture(std::string path, int x, int y, int width, int height) : Texture()
{
    mGraphics = Graphics::instance();
    mTexture  = assetManager::instance()->getTexture(path);

    mWidth = width;
    mHeight = height;

    mClipped = true;

    mClipRect.x = x;
    mClipRect.y = y;
    mClipRect.w = width;
    mClipRect.h = height;
}

Texture::Texture(std::string text, std::string filePath, int size, SDL_Color color) : Texture()
{
    mGraphics = Graphics::instance();
    mTexture  = assetManager::instance()->getTextTexture(text, filePath, size, color);

    mClipped = false;

    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
}

Texture::~Texture()
{
    mGraphics = nullptr;
    mTexture  = nullptr;
}

void Texture::setColor(int red, int green, int blue, int alpha)
{
    mRed = red;
    mGreen = green;
    mBlue = blue;

    if (alpha != -1) {
        mAlpha = alpha;
    }
}

void Texture::render()
{
    GVector pos = this->pos(world);
    GVector scaller = this->scale(world);

    mRenderRect.x = static_cast<int>(pos.x - 0.5f * mWidth * scaller.x);
    mRenderRect.y = static_cast<int>(pos.y - 0.5f * mHeight * scaller.y);

    mRenderRect.w = static_cast<int>(mWidth * scaller.x);
    mRenderRect.h = static_cast<int>(mHeight * scaller.y);

    mGraphics->setTextureColor(mTexture, mRed, mGreen, mBlue, mAlpha);
    mGraphics->drawTexture(mTexture, &mClipRect, &mRenderRect);
    mGraphics->setTextureColor(mTexture);
}

void Texture::render(int r, int g, int b, int a)
{
    GVector pos = this->pos(world);
    GVector scaller = this->scale(world);

    mRenderRect.x = static_cast<int>(pos.x - 0.5f * mWidth * scaller.x);
    mRenderRect.y = static_cast<int>(pos.y - 0.5f * mHeight * scaller.y);

    mRenderRect.w = static_cast<int>(mWidth * scaller.x);
    mRenderRect.h = static_cast<int>(mHeight * scaller.y);

    mGraphics->setTextureColor(mTexture, r, g, b, a);
    mGraphics->drawTexture(mTexture, &mClipRect, &mRenderRect);
    mGraphics->setTextureColor(mTexture);
}


void Texture::update()
{

}

void TextureUtils::copy(const Texture * & source, Texture * & destination)
{
    if (source == nullptr) {
        return;
    }


    if (destination == nullptr) {
        destination = new Texture();
    }

    *(destination) = *(source);
}