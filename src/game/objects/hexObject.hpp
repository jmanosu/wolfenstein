#ifndef HEXOBJECT
#define HEXOBJECT

#include "game/objects/gameEntity.hpp"
#include "game/objects/weapon.hpp"

#include "graphics/texture.hpp"

#include "game/utils/cubeCoord.hpp"

class HexObject : public GameEntity {
    public:
        HexObject();
        ~HexObject();

        void render();
        void update();

        void setLocation(CubeCoord);
        CubeCoord getLocation();

        virtual void applyWeapon(Weapon *);

    private:

    protected:
        Texture * mHexObjectTexture;
        CubeCoord mLocation;

};

#endif