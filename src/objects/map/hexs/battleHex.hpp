#ifndef BATTLEHEX_HPP
#define BATTLEHEX_HPP

#include "objects/map/hexs/pixelHexs/pixelHex.hpp"


class BattleHex : public PixelHex<BattleHex> {
    public:
        BattleHex();
        BattleHex(const BattleHex & hex);

        ~BattleHex();

        BattleHex * clone();
        
        void applyWeapon(Weapon *);

        void update();
};

#endif