#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include <iostream>

#include "geometry/gamingVector.hpp"

typedef int ID;

class GameEntity {
    public:
        enum SPACE {local = 0, world = 1};
    private:
        int mId;

        GVector mPos, mScale;

        float mRotation;
        
        bool mActive;

        GameEntity * mParent;

    public:
        GameEntity(float x = 0.0f, float y = 0.0f);
        ~GameEntity();

        int id() const;

        void pos(GVector pos);
        GVector pos(SPACE space = world);

        void scale(GVector scale);
        GVector scale(SPACE space = world);

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