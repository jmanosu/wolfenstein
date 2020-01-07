#ifndef HEXOBJECT
#define HEXOBJECT

#include "game/objects/gameEntity.hpp"

class HexObject : public GameEntity {
    public:
        HexObject();
        ~HexObject();

        void render();
        void update();

};

#endif