#ifndef BATTLEHEX_HPP
#define BATTLEHEX_HPP

#include "objects/map/hexs/hex.hpp"

class BattleHex : public Hex {
    public:
        BattleHex();
        BattleHex(const BattleHex & hex);

        ~BattleHex();

        Hex * clone();

        void setHexTexture(const Texture *);
        void setSkirtTexture(const Texture *);
        void setHighlightTexture(const Texture *, Direction);

        void renderHighlight();

        void renderBackground();
        void renderMidground();
        void renderForground();

        void render();

    private:
        //Hex Textures;
        Texture * mHexTexture;
        Texture * mSkirtTexture;

        std::vector<Texture *>  mHighlightTextures;
};

#endif