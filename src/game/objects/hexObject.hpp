#ifndef HEXOBJECT
#define HEXOBJECT

#include "game/objects/gameEntity.hpp"
#include "graphics/texture.hpp"

class HexObject : public GameEntity {
    public:
        HexObject();
        ~HexObject();

        void render();
        void update();

    private:
        Texture * mHexObjectTexture;

};

#endif