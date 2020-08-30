#include "gameEntity.hpp"

#include "utils/idGenerator.hpp"

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
}

GameEntity::GameEntity(const GameEntity & entity) : GameEntity(0,0)
{
    mPos.x = entity.mPos.x;
    mPos.y = entity.mPos.y;

    mScale.x = entity.mScale.x;
    mScale.y = entity.mScale.y;

    mRotation = entity.mRotation;

    mActive = entity.mActive;

    mParent = entity.mParent;
}

GameEntity::~GameEntity()
{
}

int GameEntity::id() const
{
    return mId;
}

void GameEntity::pos(const GVector pos)
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