#ifndef PIXELHEX_HPP
#define PIXELHEX_HPP

#include "graphics/textures/animatedTexture.hpp"

#include "objects/map/hexs/hex.hpp"

template  <typename _Hex> class PixelHex : public Hex<_Hex> {
    public:
        PixelHex();
        PixelHex(const PixelHex & hex);

        ~PixelHex();

        void setHexTexture(const Texture *);
        void setHexOverlayTexture(const Texture *);
        void setSkirtTexture(const Texture *);
        
        void setBorderTexture(const Texture *, Direction);

        void setHexOverlayColor(int, int, int, int);
        void setBorderColor(int, int, int, int);

        void renderBorder(int, RGBA);

        void renderBackground();
        void renderMidground();
        void renderForground();

        void render();

        bool getRenderBorder();

        RGBA getBorderColor();

    protected:
        //Hex Textures;
        Texture * mHexTexture;
        Texture * mHexOverlayTexture;
        Texture * mSkirtTexture;

        std::vector<Texture *> mBorderTextures;

        bool mRenderBorders, mRenderOverlay;

        RGBA mOverlayColor, mBorderColor;
};

template <class _Hex> PixelHex<_Hex>::PixelHex() : Hex<_Hex>(),
    mHexTexture(nullptr),
    mHexOverlayTexture(nullptr),
    mSkirtTexture(nullptr),

    mBorderTextures(int(NorthWest) + 1, nullptr),

    mRenderBorders(false),
    mRenderOverlay(false)
{
    for (size_t i = North; i <= NorthWest; i++) {
        mBorderTextures.at(i) = nullptr;
    }
}

template <class _Hex> PixelHex<_Hex>::PixelHex(const PixelHex & hex) : Hex<_Hex>(hex),
    mHexTexture(nullptr),
    mHexOverlayTexture(nullptr),
    mSkirtTexture(nullptr),

    mBorderTextures(int(NorthWest) + 1, nullptr),

    mRenderBorders(false),
    mRenderOverlay(false)
{
    setHexTexture(hex.mHexTexture);
    setSkirtTexture(hex.mSkirtTexture);

    for (size_t i = North; i <= NorthWest; i++) {
        setBorderTexture(hex.mBorderTextures.at(i), (Direction) i);
    }

}


template <class _Hex> PixelHex<_Hex>::~PixelHex()
{
    delete mHexTexture;
    delete mSkirtTexture;

    for (size_t i = North; i <= NorthWest; i++) {
        delete mBorderTextures.at(i);
    }
}

template <class _Hex> void PixelHex<_Hex>::setHexTexture(const Texture * hexTexture)
{
    TextureUtils::copy(hexTexture, mHexTexture);
    if (mHexTexture != nullptr) {
      mHexTexture->parent(this);
    }
}

template <class _Hex> void PixelHex<_Hex>::setHexOverlayTexture(const Texture * hexOverlayTexture)
{
    TextureUtils::copy(hexOverlayTexture, mHexOverlayTexture);
    if (mHexOverlayTexture != nullptr) {
        mHexOverlayTexture->parent(this);
    }
}

template <class _Hex> void PixelHex<_Hex>::setSkirtTexture(const Texture * skirtTexture)
{
    TextureUtils::copy(skirtTexture, mSkirtTexture);
    if (mSkirtTexture != nullptr) {
      mSkirtTexture->parent(this);
    }
}

template <class _Hex> void PixelHex<_Hex>::setBorderTexture(const Texture * borderTexture, Direction direction)
{
    TextureUtils::copy(borderTexture, mBorderTextures.at(direction));
    if (mBorderTextures.at(direction) != nullptr) {
      mBorderTextures.at(direction)->parent(this);
    }
}

template <class _Hex> void PixelHex<_Hex>::setHexOverlayColor(int r, int g, int b, int a)
{
    mHexOverlayTexture->setColor(r, g, b, a);
}

template <class _Hex> void PixelHex<_Hex>::setBorderColor(int r, int g, int b, int a)
{
    mBorderColor.r = r;
    mBorderColor.g = g;
    mBorderColor.b = b;
    mBorderColor.a = a;
}

template <class _Hex> void PixelHex<_Hex>::renderBorder(int i, RGBA rgba)
{
    if (mBorderTextures.at(i) != nullptr) {
        mBorderTextures.at(i)->render(rgba.r, rgba.g, rgba.b, rgba.a);
    }
}

template <class _Hex> void PixelHex<_Hex>::renderBackground()
{
    if (mSkirtTexture != nullptr) {
      mSkirtTexture->render();
    }

    if (mHexTexture != nullptr) {
      mHexTexture->render();
    }

    if (mRenderOverlay && mHexOverlayTexture != nullptr) {
        mHexOverlayTexture->render();
    }

    for (size_t i = North; i <= NorthWest; i++) {
        PixelHex<_Hex> * neighbor = PixelHex<_Hex>::getNeighbor((Direction)i);
        if ((neighbor != nullptr && neighbor->getRenderBorder()) && (i < SouthEast || i > SouthWest)) {
            renderBorder(i, neighbor->getBorderColor());
        }
        if (mRenderBorders) {
            renderBorder(i, mBorderColor);
        }
    }

}

template <class _Hex> void PixelHex<_Hex>::renderMidground()
{

    if (this->mHexObject != nullptr) {
      this->mHexObject->render();
    }
}

template <class _Hex> void PixelHex<_Hex>::renderForground()
{

}

template <class _Hex> void PixelHex<_Hex>::render()
{
    renderBackground();
    renderMidground();
    renderForground();
}

template <class _Hex> bool PixelHex<_Hex>::getRenderBorder()
{
    return mRenderBorders;
}

template <class _Hex> RGBA PixelHex<_Hex>::getBorderColor()
{
    return mBorderColor;
}

#endif