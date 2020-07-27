#ifndef HEXOBJECT_HPP
#define HEXOBJECT_HPP

#include "objects/gameEntity.hpp"
#include "objects/map/weapons/weapon.hpp"

#include "graphics/textures/texture.hpp"

#include "geometry/cubeCoord.hpp"

class HexObject : public GameEntity {
    public:
        HexObject();
        ~HexObject();

        void render();
        void update();

        void setLocation(CubeCoord);
        CubeCoord getLocation();

        void setPlaced(bool);
        bool getPlaced();

        virtual void applyWeapon(Weapon *);

    private:

    protected:
        Texture * mHexObjectTexture;
        CubeCoord mLocation;

        bool _placed;

};

#endif