#include "hexTexture.hpp"

HexTexture::HexTexture(std::string path, int hexWidth, int hexHeight, int peakHeight) : Texture(path)
{
    this->mHexWidth = hexWidth;
    this->mHexHeight = hexHeight;
    this->mPeakHeight = peakHeight;
}

HexTexture::~HexTexture()
{

}

void HexTexture::renderHex()
{
    GVector pos = this->pos(world);
    GVector scaller = this->scale(world);

    mRenderRect.x = static_cast<int>(pos.x - 0.5f * mWidth / 2 * scaller.x);
    mRenderRect.y = static_cast<int>(pos.y - 0.5f * mHeight * scaller.y);

    mRenderRect.w = static_cast<int>(mWidth / 2 * scaller.x);
    mRenderRect.h = static_cast<int>(mHeight * scaller.y);

    SDL_Rect clipRect = {0, 0, (mWidth / 2), mHeight};

    mGraphics->drawTexture(mTexture, &clipRect, &mRenderRect);
}

void HexTexture::renderLeftCascade()
{
    GVector pos = this->pos(world);
    GVector scaller = this->scale(world);

    mRenderRect.x = static_cast<int>(pos.x - 0.5f * mWidth / 2 * scaller.x);
    mRenderRect.y = static_cast<int>(pos.y - 0.5f * mHeight * scaller.y);

    mRenderRect.w = static_cast<int>((mWidth / 4) * scaller.x);
    mRenderRect.h = static_cast<int>(mHeight * scaller.y);

    SDL_Rect clipRect = {(mWidth / 2), 0, (mWidth / 4), mHeight};

    mGraphics->drawTexture(mTexture, &clipRect, &mRenderRect);
}

void HexTexture::renderRightCascade()
{
    GVector pos = this->pos(world);
    GVector scaller = this->scale(world);

    mRenderRect.x = static_cast<int>(pos.x + 0.5f * scaller.x);
    mRenderRect.y = static_cast<int>(pos.y - 0.5f * mHeight * scaller.y);

    mRenderRect.w = static_cast<int>((mWidth / 4) * scaller.x);
    mRenderRect.h = static_cast<int>(mHeight * scaller.y);

    SDL_Rect clipRect = {(mWidth * 3 / 4 + 1), 0, (mWidth / 4), mHeight};

    mGraphics->drawTexture(mTexture, &clipRect, &mRenderRect);

}

void HexTexture::render()
{
    renderHex();

    GVector pos = this->pos(world);
    GVector scaller = this->scale(world);

    mRenderRect.x = static_cast<int>(pos.x - 0.5f * mWidth / 2 * scaller.x);
    mRenderRect.y = static_cast<int>(pos.y - 0.5f * mHeight * scaller.y);

    mRenderRect.w = static_cast<int>(mWidth / 2 * scaller.x);
    mRenderRect.h = static_cast<int>(mHeight * scaller.y);

    SDL_Rect clipRect = {(mWidth / 2), 0, (mWidth / 2), mHeight};

    mGraphics->drawTexture(mTexture, &clipRect, &mRenderRect);    
}
/* 
void HexTexture::render(double centerX, double centerY, double customWidth)
{
    double ratioHW = (double)height / (double)width;
    double ratioWH = (double)width / (double)height;
    double customHeight = ratioHW * customWidth;
    std::cout << "customHeight: " << customHeight << " customWidth: " << customWidth <<  " ratioHW: " << ratioHW << std::endl;
    std::cout << "centerX :" << this->centerX << " width: " << width << std::endl;
    Texture::render(centerX - customWidth / 2 - 1, centerY - this->centerY * ratioHW, customWidth, customHeight);
//    Texture::render(centerX - this->centerX, centerY - this->centerY, width, height);
    Graphics::instance()->drawPoint(centerX - this->centerX, centerY - this->centerY);
}
*/