#include "gameEntity.hpp"

#include "game/utils/idGenerator.hpp"

GameEntity::GameEntity(float x, float y)
{
    mId = IdGenerator::instance()->generateId();

    mPos.x = x;
    mPos.y = y;

    mScale.x = 1;
    mScale.y = 1;

    mRotation = 0.0f;

    mActive = false;

    mParent = nullptr;

    mClicked = false, mPressed = false, mHovered = false;
}

GameEntity::~GameEntity()
{
}

int GameEntity::id() const
{
    return mId;
}

void GameEntity::pos(GVector pos)
{
    mPos = pos;
}

GVector GameEntity::pos(SPACE space)
{
    if(space == local || mParent == nullptr)
    {
        return mPos;
    }

    GVector scale = mParent->scale();
    GVector rotPos = RotateVector(mPos, mParent->rotation(local));

    rotPos.x = rotPos.x * mParent->scale().x;
    rotPos.y = rotPos.y * mParent->scale().y;

    return mParent->pos(world) + rotPos;
}

void GameEntity::scale(GVector scale)
{
    mScale = scale;
}

GVector GameEntity::scale(SPACE space)
{
    if(space == local || mParent == nullptr)
    {
        return mScale;
    }

    GVector scale = mParent->scale();
    scale.x *= mScale.x;
    scale.y *= mScale.y;
    return scale;
}

void GameEntity::rotation(float rotation)
{
    mRotation = rotation;
}

float GameEntity::rotation(SPACE space)
{
    if(space == local || mParent == nullptr)
    {
        return mRotation;
    }

    return mParent->rotation(world) + mRotation;
}

void GameEntity::active(bool active)
{
    mActive = active;
}

bool GameEntity::active()
{
    return mActive;
}

void GameEntity::parent(GameEntity * newParent)
{
    mParent = newParent;
}

GameEntity * GameEntity::parent()
{
    return mParent;
}

void GameEntity::update()
{

}

void GameEntity::render()
{
    
}

void GameEntity::setClicked(bool clicked)
{
    mClicked = clicked;
}

void GameEntity::setPressed(bool pressed)
{
    mPressed = pressed;
}

void GameEntity::setHovered(bool hovered)
{
    mHovered = hovered;
}

bool GameEntity::getClicked()
{
    return mClicked;
}

bool GameEntity::getPressed()
{
    return mPressed;
}

bool GameEntity::getHovered()
{
    return mHovered;
}