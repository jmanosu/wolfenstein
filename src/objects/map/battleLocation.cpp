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

void BattleTile::setHexObject(HexObject * hexObject)
{
    HexTile::setHexObject(hexObject);
    _hexObjectType = HexObjectType::hexObject;
}

void BattleTile::setHexObject(Unit * unit)
{
    HexTile::setHexObject(unit);
    _hexObjectType = HexObjectType::unit;
}

void BattleTile::releaseHexObject()
{
    HexTile::releaseHexObject();
    _hexObjectType = HexObjectType::none;
}

BattleTile::HexObjectType BattleTile::getHexObjectType()
{
    return _hexObjectType;
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
    if (_hexObjectType == HexObjectType::unit) {
        return static_cast<Unit *>(_hexObject);
    } else {
        return nullptr;
    }
}