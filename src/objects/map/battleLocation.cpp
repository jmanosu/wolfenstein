#include "battleLocation.hpp"

BattleTile::BattleTile() : HexTile(),
    _visited(false),

    _neighbors(6, nullptr)
{

}

BattleTile::~BattleTile()
{
    
}

void BattleTile::setVisited(bool visited)
{
    _visited = visited;
}

void BattleTile::setNeighbor(HexSide side, BattleTile * tile)
{
    if (side < 0  || side > 5) {
        return;
    }

    _neighbors.at(side) = tile;

    if (_hex != nullptr && tile != nullptr) {
        _hex->addNeighbor(tile->getHex(), (Direction)side);
    }
}

BattleTile * BattleTile::getNeighbor(HexSide side)
{
    if (side < 0  || side > 5) {
        return nullptr;
    }

    return _neighbors.at(side);
}

bool BattleTile::getVisted()
{
    return _visited;
}

Unit * BattleTile::getUnit()
{
    return static_cast<Unit *>(_hexObject);
}