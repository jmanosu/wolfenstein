#ifndef HEXCOLLECTION_HPP
#define HEXCOLLECTION_HPP

#include <map>

#include "objects/map/hexs/battleHex.hpp"

class HexCollectionEntry {
    public:
        HexCollectionEntry();
        HexCollectionEntry(BattleHex *, int);
        ~HexCollectionEntry();

        void setBattleHex(BattleHex *);
        BattleHex * getBattleHex();

        void setDistance(int);
        int getDistance();

    private:
        BattleHex * mBattleHex;
        int mDistance;
};


class HexCollection {
    public:
        HexCollection();
        ~HexCollection();

        void addHex(CubeCoord, HexCollectionEntry);
        void remove(CubeCoord);

        HexCollectionEntry getHex(CubeCoord);

        void setHighlight(bool);
        bool getHighlight();

        void setCenter(CubeCoord);
        CubeCoord getCenter();

        void drawPath(CubeCoord);

    private:
        CubeCoord mCenter;

        bool mHighlight;

        std::map<CubeCoord, HexCollectionEntry> mGrid;
};

#endif