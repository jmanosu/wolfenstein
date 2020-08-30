#ifndef HEXEFFECT_HPP
#define HEXEFFECT_HPP

#include "objects/gameEntity.hpp"

#include "objects/map/battleLocation.hpp"

class HexEffect : public GameEntity{
    public:
        HexEffect();
        ~HexEffect();

        void render();
        void update();

        void apply(BattleTile *);

    private:

};

#endif