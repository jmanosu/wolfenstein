#ifndef BATTLEHEX_HPP
#define BATTLEHEX_HPP

#include "objects/map/hexs/pixelHex.hpp"


class BattleHex : public PixelHex<BattleHex> {
    public:
        BattleHex();
        BattleHex(const BattleHex & hex);

        ~BattleHex();

        enum BattleHexType {
            land = 0,
            water
        };

        BattleHex * clone();
        
        void applyWeapon(Weapon *);

        void update();

        void setHighlight(bool);

        void setType(BattleHexType type);

        BattleHexType getType();
    private:
        RGBA mFocusColor;
        RGBA mHighlightColor;

        bool mHighlight;

        BattleHexType _type;
};

#endif