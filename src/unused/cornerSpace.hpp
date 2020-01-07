#ifndef SPACE_HPP
#define SPACE_HPP

#include "gameEntity.hpp"
#include "graphics.hpp"
#include "gamingVector.hpp"

class CornerSpace : public GameEntity {
    public:
        CornerSpace();
        ~CornerSpace();

        void render();
        void update();

};

#endif