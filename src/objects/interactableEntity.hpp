#ifndef INTERACTABLEENTITY_HPP
#define INTERACTABLEENTITY_HPP

#include "objects/gameEntity.hpp"

class InteractableEntity : public GameEntity {
    public:
        InteractableEntity(float x = 0.0f, float y = 0.0f);
        ~InteractableEntity();

        bool getHovered();
        bool getClicked();
        bool getPressed();
        bool getReleased();

        void setHovered(bool);
        void setClicked(bool);
        void setPressed(bool);
        void setReleased(bool);

    protected:
        bool mHovered, mClicked, mPressed, mReleased;
};

#endif