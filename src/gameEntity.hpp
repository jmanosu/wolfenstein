#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP
#include "gamingVector.hpp"
#include <iostream>

class GameEntity{
    public:
        enum SPACE {local = 0, world = 1};
    private:
        GVector::GVector mPos, mScale;
        float mRotation;
        bool mActive;
        GameEntity * mParent;
    public:
        GameEntity(float x = 0.0f, float y = 0.0f);
        ~GameEntity();

        void pos(GVector::GVector pos);
        GVector::GVector pos(SPACE space = world);

        void scale(GVector::GVector scale);
        GVector::GVector scale(SPACE space = world);

        void rotation(float rotation);
        float rotation(SPACE space = world);

        void active(bool active);
        bool active();

        void parent(GameEntity *);
        GameEntity * parent();
        
        virtual void update();
        virtual void render();
};

#endif