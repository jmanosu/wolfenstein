#ifndef HEXCOLLECTION_HPP
#define HEXCOLLECTION_HPP

#include <map>

#include "objects/map/hexs/battleHex.hpp"

#include "objects/map/battleLocation.hpp"

class HexCollectionEntry {
    public:
        HexCollectionEntry();
        HexCollectionEntry(BattleTile *, int);
        ~HexCollectionEntry();

        void setBattleHex(BattleTile *);
        BattleTile * getBattleHex();

        void setDistance(int);
        int getDistance();

    private:
        BattleTile * mBattleHex;
        int mDistance;
};


class HexCollection {
    public:
        HexCollection();
        ~HexCollection();

        void addTile(CubeCoord, HexCollectionEntry);
        void remove(CubeCoord);

        bool checkEntry(CubeCoord);
        HexCollectionEntry getEntry(CubeCoord);

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