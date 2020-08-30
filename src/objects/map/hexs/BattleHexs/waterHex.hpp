#ifndef WATERHEX_HPP
#define WATERHEX_HPP

#include "objects/map/hexs/battleHex.hpp"

class WaterHex : public BattleHex {
    public:
        WaterHex();
        ~WaterHex();

        void update();

    private:
        AnimatedTexture * _waterHexTexture;
};

#endif