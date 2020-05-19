#include "interactableEntity.hpp"

InteractableEntity::InteractableEntity(float x, float y) : GameEntity(x, y),
    mHovered(false),
    mClicked(false),
    mPressed(false),
    mReleased(false)
{

}

InteractableEntity::~InteractableEntity()
{

}

bool InteractableEntity::getHovered()
{
    return mHovered;
}

bool InteractableEntity::getClicked()
{
    return mClicked;
}

bool InteractableEntity::getPressed()
{
    return mPressed;
}

bool InteractableEntity::getReleased()
{
    return mReleased;
}

void InteractableEntity::setHovered(bool hovered)
{
    mHovered = hovered;
}

void InteractableEntity::setClicked(bool clicked)
{
    mClicked = clicked;
}

void InteractableEntity::setPressed(bool pressed)
{
    mPressed = pressed; 
}

void InteractableEntity::setReleased(bool released)
{
    mReleased = released;
}