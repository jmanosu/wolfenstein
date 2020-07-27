#ifndef BATTLELOCATION_HPP
#define BATTLELOCATION_HPP

#include <vector>

#include "objects/map/hexLocation.hpp"
#include "objects/map/hexs/battleHex.hpp"
#include "objects/map/hexObjects/hexObject.hpp"
#include "objects/map/hexObjects/units/unit.hpp"

class BattleTile : public HexTile<BattleHex, HexObject> {
    public:
        BattleTile();
        ~BattleTile();

        void setVisited(bool);
        void setNeighbor(HexSide, BattleTile *);

        BattleTile * getNeighbor(HexSide);

        bool getVisted();

        Unit * getUnit();

    private:
        bool _visited;

        std::vector<BattleTile *> _neighbors;
};

#endif