#include "battleHex.hpp"

BattleHex::BattleHex() : Hex(),
    mHexTexture(nullptr),
    mSkirtTexture(nullptr),
    mHighlightTextures(int(NorthWest) + 1, nullptr)
{
    for (size_t i = North; i <= NorthWest; i++) {
        mHighlightTextures.at(i) = nullptr;
    }
}

BattleHex::BattleHex(const BattleHex & hex) : Hex(hex),
    mHexTexture(nullptr),
    mSkirtTexture(nullptr),
    mHighlightTextures(int(NorthWest) + 1, nullptr)
{
    setHexTexture(hex.mHexTexture);
    setSkirtTexture(hex.mSkirtTexture);

    for (size_t i = North; i <= NorthWest; i++) {
        setHighlightTexture(hex.mHighlightTextures.at(i), (Direction) i);
    }

}


BattleHex::~BattleHex()
{
    delete mHexTexture;
    delete mSkirtTexture;

    for (size_t i = North; i <= NorthWest; i++) {
        delete mHighlightTextures.at(i);
    }
}

Hex * BattleHex::clone()
{
    return new BattleHex(*(this));
}

void BattleHex::setHexTexture(const Texture * hexTexture)
{
  TextureUtils::copy(hexTexture, mHexTexture);
  mHexTexture->parent(this);
}

void BattleHex::setSkirtTexture(const Texture * skirtTexture)
{
  TextureUtils::copy(skirtTexture, mSkirtTexture);
  mSkirtTexture->parent(this);
}

void BattleHex::setHighlightTexture(const Texture * highlightTexture, Direction direction)
{
    TextureUtils::copy(highlightTexture, mHighlightTextures.at(direction));
    mHighlightTextures.at(direction)->parent(this);
}

void BattleHex::renderHighlight()
{
  for (size_t i = North; i <= NorthWest; i++) {
    if ((mNeighbors.at(i) != nullptr && mNeighbors.at(i)->getHovered() && (i < SouthEast || i > SouthWest)) || getHovered()) {
      if (mHighlightTextures.at(i) != nullptr) {
        mHighlightTextures.at(i)->render();
      }
    }
  }
}

void BattleHex::renderBackground()
{
  if (mSkirtTexture != nullptr) {
    mSkirtTexture->render();
  }

  if (mHexTexture != nullptr) {
    mHexTexture->render();
  }

  renderHighlight();
}

void BattleHex::renderMidground()
{
  if (mHexObject != nullptr) {
    mHexObject->render();
  }
}

void BattleHex::renderForground()
{

}

void BattleHex::render()
{
    renderBackground();
    renderMidground();
    renderForground();
}
