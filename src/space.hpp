#ifndef SPACE_HPP
#define SPACE_HPP

#include "gameEntity.hpp"
#include "graphics.hpp"
#include "gamingVector.hpp"

class Space : public GameEntity {
    public:
        Space();
        ~Space();

        void render();
        void update();

};

#endif