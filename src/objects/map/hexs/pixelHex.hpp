#ifndef PIXELHEX_HPP
#define PIXELHEX_HPP

#include "graphics/textures/animatedTexture.hpp"

#include "objects/map/hexs/hex.hpp"

enum PixelMode {
    Standard = 0,
    Highlight,
    GroupHighlight
};

template  <typename _Hex> class PixelHex : public Hex<_Hex> {
    public:
        PixelHex();
        PixelHex(const PixelHex & hex);

        ~PixelHex();

        void setHexTexture(const Texture *);
        void setHexOverlayTexture(const Texture *);
        void setSkirtTexture(const Texture *);
        
        void setBorderTexture(const Texture *, Direction);
        void setPathTexture(const Texture &, Direction);

        void setHexOverlayColor(RGBA);
        void setHexOverlayColor(int, int, int,  int);

        void setBorderColor(RGBA);
        void setBorderColor(int, int, int,  int);

        void setPixelMode(PixelMode);

        void setPathEnterence(Direction);
        void setPathExit(Direction);

        void renderBorder(int, RGBA);

        void renderBackground();
        void renderMidground();
        void renderForground();

        void render();

        void setRenderOverride(bool);
        void setRenderBorder(bool);
        void setRenderGroupOverlay(bool);
        void setRenderOverlay(bool);

        void setRenderPathEnterence(bool);
        void setRenderPathExit(bool);

        bool getRenderOverride();
        bool getRenderBorder();
        bool getRenderGroupOverlay();
        bool getRenderOverlayBorder();

        RGBA getBorderColor();

    protected:
        PixelMode mPixelMode;

        Direction mPathEnterence;
        Direction mPathExit;

        //Hex Textures;
        Texture * mHexTexture;
        Texture * mHexOverlayTexture;
        Texture * mSkirtTexture;

        std::vector<Texture *> mBorderTextures;

        std::vector<Texture> mPathTextures;

        RGBA mBorderColor;
    private:
        bool mRenderOverride;

        bool mRenderBorder, mRenderOverlay;

        bool mRenderGroup;

        bool mRenderPathEnterence, mRenderPathExit;

        
};

template <class _Hex> PixelHex<_Hex>::PixelHex() : Hex<_Hex>(),
    mPixelMode(PixelMode::Standard),

    mPathEnterence(Direction::North),
    mPathExit(Direction::North),

    mHexTexture(nullptr),
    mHexOverlayTexture(nullptr),
    mSkirtTexture(nullptr),

    mBorderTextures(int(NorthWest) + 1, nullptr),

    mPathTextures(int(NorthWest) + 1, Texture()),

    mRenderBorder(false),
    mRenderOverlay(false),
    mRenderGroup(false),

    mRenderOverride(false),

    mRenderPathEnterence(false),
    mRenderPathExit(false)
{
    for (size_t i = North; i <= NorthWest; i++) {
        mBorderTextures.at(i) = nullptr;
    }
}

template <class _Hex> PixelHex<_Hex>::PixelHex(const PixelHex & hex) : Hex<_Hex>(hex),
    mPixelMode(PixelMode::Standard),

    mPathEnterence(Direction::North),
    mPathExit(Direction::North),

    mHexTexture(nullptr),
    mHexOverlayTexture(nullptr),
    mSkirtTexture(nullptr),

    mBorderTextures(int(NorthWest) + 1, nullptr),

    mPathTextures(int(NorthWest) + 1, Texture()),

    mRenderBorder(false),
    mRenderOverlay(false),
    mRenderGroup(false),

    mRenderOverride(false),

    mRenderPathEnterence(false),
    mRenderPathExit(false)
{
    setHexTexture(hex.mHexTexture);
    setHexOverlayTexture(hex.mHexOverlayTexture);
    setSkirtTexture(hex.mSkirtTexture);

    for (size_t i = North; i <= NorthWest; i++) {
        setBorderTexture(hex.mBorderTextures.at(i), (Direction) i);
    }

    for (size_t i = North; i <= NorthWest; i++) {
        setPathTexture(hex.mPathTextures.at(i), (Direction) i);
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

template <class _Hex> void PixelHex<_Hex>::setPathTexture(const Texture & texture, Direction direction)
{
    mPathTextures.at(direction) = texture;
    mPathTextures.at(direction).parent(this);
}

template <class _Hex> void PixelHex<_Hex>::setHexOverlayColor(RGBA color)
{
    mHexOverlayTexture->setColor(color.r, color.g, color.b, color.a);
}

template <class _Hex> void PixelHex<_Hex>::setHexOverlayColor(int r, int g, int b, int a)
{
    mHexOverlayTexture->setColor(r, g, b, a);
}

template <class _Hex> void PixelHex<_Hex>::setBorderColor(RGBA color)
{
    mBorderColor = color;
}

template <class _Hex> void PixelHex<_Hex>::setBorderColor(int r, int g, int b, int a)
{
    mBorderColor.r = r;
    mBorderColor.g = g;
    mBorderColor.b = b;
    mBorderColor.a = a;
}

template <class _Hex> void PixelHex<_Hex>::setPixelMode(PixelMode mode)
{
    mPixelMode = mode;

    switch (mPixelMode) {
        case PixelMode::Standard:
            mRenderBorder = false;
            mRenderOverlay = false;
            mRenderGroup = false;
            break;        
        case PixelMode::Highlight:
            mRenderBorder = true;
            mRenderOverlay = true;
            mRenderGroup = false;
            break;
        case PixelMode::GroupHighlight:
            mRenderBorder = true;
            mRenderOverlay = true;
            mRenderGroup = true;
            break;
        default:
            break;
    }
}

template<class _Hex> void PixelHex<_Hex>::setPathEnterence(Direction direction)
{
    mPathEnterence = direction;
}

template<class _Hex> void PixelHex<_Hex>::setPathExit(Direction direction)
{
    mPathExit = direction;
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
}

template <class _Hex> void PixelHex<_Hex>::renderMidground()
{
    if (mRenderOverlay && mHexOverlayTexture != nullptr) {
        mHexOverlayTexture->render();
    }

    for (size_t i = North; i <= NorthWest; i++) {
        PixelHex<_Hex> * neighbor = PixelHex<_Hex>::getNeighbor((Direction)i);

        if (mRenderOverride) {
            if (mRenderBorder) {
                renderBorder(i, mBorderColor);
                continue;
            }
        }


        switch (mPixelMode) {
            case PixelMode::Standard:
                if (neighbor != nullptr && neighbor->getRenderBorder() && neighbor->getDepth() == PixelHex::getDepth()) {
                    renderBorder(i, neighbor->getBorderColor());
                }
                break;
            case PixelMode::Highlight:
                if (neighbor != nullptr && neighbor->getRenderOverride() && neighbor->getDepth() == PixelHex::getDepth()) {
                    renderBorder(i, neighbor->getBorderColor());
                } else {
                    renderBorder(i, mBorderColor);
                }
                break;
            case PixelMode::GroupHighlight:
                if (neighbor != nullptr) {
                    if (neighbor->getRenderOverride() && neighbor->getDepth() == PixelHex::getDepth()) {
                        renderBorder(i, neighbor->getBorderColor());
                    } else if (!neighbor->getRenderGroupOverlay() || !mRenderGroup) {
                        renderBorder(i, mBorderColor);
                    }
                } else {
                    renderBorder(i, mBorderColor);
                }
                break;            
            default:
                break;
        }
    }

    if (mRenderPathEnterence) {
        mPathTextures.at(mPathEnterence).render();
    }

    if (mRenderPathExit) {
        mPathTextures.at(mPathExit).render();
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

template <class _Hex> void PixelHex<_Hex>::setRenderOverride(bool renderOveride)
{
    setPixelMode(mPixelMode);
    mRenderOverride = renderOveride;
}

template <class _Hex> void PixelHex<_Hex>::setRenderBorder(bool renderBorder)
{
    if (mRenderOverride) {
        mRenderBorder = renderBorder;
    }
}

template <class _Hex> void PixelHex<_Hex>::setRenderGroupOverlay(bool renderGroupOverlay)
{
    if (mRenderOverride) {
        mRenderGroup = renderGroupOverlay;
    }
}

template <class _Hex> void PixelHex<_Hex>::setRenderOverlay(bool renderOverlay)
{
    if (mRenderOverride) {
        mRenderOverlay = renderOverlay;
    }
}

template <class _Hex> void PixelHex<_Hex>::setRenderPathEnterence(bool render)
{
    mRenderPathEnterence = render;
}

template <class _Hex> void PixelHex<_Hex>::setRenderPathExit(bool render)
{
    mRenderPathExit = render;
}

template <class _Hex> bool PixelHex<_Hex>::getRenderOverride()
{
    return mRenderOverride;
}

template <class _Hex> bool PixelHex<_Hex>::getRenderBorder()
{
    return mRenderBorder;
}

template <class _Hex> bool PixelHex<_Hex>::getRenderGroupOverlay()
{
    return mRenderGroup;
}

template <class _Hex> bool PixelHex<_Hex>::getRenderOverlayBorder()
{
    return mRenderOverlay;
}

template <class _Hex> RGBA PixelHex<_Hex>::getBorderColor()
{
    return mBorderColor;
}

#endif