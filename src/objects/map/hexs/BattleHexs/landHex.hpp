#ifndef LANDHEX_HPP
#define LANDHEX_HPP

#include "objects/map/hexs/battleHex.hpp"

class LandHex : public BattleHex {
    public:
        LandHex();
        ~LandHex();

        enum LandHexType {
            grass = 0,
            desert,
            snow
        };

        void setType(LandHexType);
    
    private:
        LandHexType _type;

        Texture * _grassHexTexture;
        Texture * _desertHexTexture;
        Texture * _snowHexTexture;
};

#endif