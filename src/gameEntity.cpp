#include "gameEntity.hpp"

GameEntity::GameEntity(float x, float y)
{
    mPos.x = x;
    mPos.y = y;

    mRotation = 0.0f;

    mActive = false;

    mParent = nullptr;
}

GameEntity::~GameEntity()
{
}

void GameEntity::pos(GVector::GVector pos)
{
    mPos = pos;
}

GVector::GVector GameEntity::pos(SPACE space)
{
    if(space == local || mParent == nullptr)
    {
//        std::cout << "mParent: " << mParent << std::endl;
        return mPos;
    }

    return mParent->pos(world) + RotateVector(mPos, mParent->mRotation);
}

void GameEntity::scale(GVector::GVector scale)
{
    mScale = scale;
}

GVector::GVector GameEntity::scale(SPACE space)
{
    if(space == local || mParent == nullptr)
    {
        return mScale;
    }

    GVector::GVector scale = mParent->scale(world);
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
    mPos = pos(world);
    mScale = scale(world);
    mRotation = rotation(world); 
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