#include "hexCollection.hpp"

//HexCollectionEntry

HexCollectionEntry::HexCollectionEntry() :
    mBattleHex(nullptr),
    mDistance(-1)
{

}

HexCollectionEntry::HexCollectionEntry(BattleTile * battleHex, int distance) :
    mBattleHex(battleHex),
    mDistance(distance)
{

}

HexCollectionEntry::~HexCollectionEntry()
{

}

void HexCollectionEntry::setBattleHex(BattleTile * battleHex)
{
    mBattleHex = battleHex;
}

BattleTile * HexCollectionEntry::getBattleHex()
{
    return mBattleHex;
}

void HexCollectionEntry::setDistance(int distance)
{
    mDistance = distance;
}

int HexCollectionEntry::getDistance()
{
    return mDistance;
}


//HexCollection

HexCollection::HexCollection() :
    mHighlight(false)
{

}

HexCollection::~HexCollection()
{

}

void HexCollection::addTile(CubeCoord location, HexCollectionEntry hexEntry)
{
    mGrid[location] = hexEntry;
}

void HexCollection::remove(CubeCoord location)
{
    typename std::map<CubeCoord, HexCollectionEntry>::iterator it = mGrid.find(location);

    if (it != mGrid.end()) {
        mGrid.erase(it);
    }
}

bool HexCollection::checkEntry(CubeCoord location)
{
    typename std::map<CubeCoord, HexCollectionEntry>::iterator it = mGrid.find(location);

    if (it != mGrid.end()) {
        return true;
    } else {
        return false;
    }
}

HexCollectionEntry HexCollection::getEntry(CubeCoord location)
{
    typename std::map<CubeCoord, HexCollectionEntry>::iterator it = mGrid.find(location);

    if (it != mGrid.end()) {
        return it->second;
    } else {
        return HexCollectionEntry();
    }
}

void HexCollection::setHighlight(bool highlight)
{
    for (typename std::pair<CubeCoord, HexCollectionEntry> pair : mGrid) {
        BattleTile * tile = pair.second.getBattleHex();
        if (tile != nullptr) {
            tile->getHex()->setHighlight(highlight);
        }
    }
}

bool HexCollection::getHighlight()
{
    return mHighlight;
}

void HexCollection::setCenter(CubeCoord center)
{
    mCenter = center;
}

CubeCoord HexCollection::getCenter()
{
    return mCenter;
}

void HexCollection::drawPath(CubeCoord location)
{
    CubeCoord currentLocation = location;
/*
    while (currentLocation != mCenter) {
        HexCollectionEntry entry = getHex(currentLocation);
        if (entry.getBattleHex() != nullptr) {
            for (size_t i = North; i <= NorthWest; i++) {
                HexCollectionEntry candidate = getHex(currentLocation + getCubeCoord((Direction)i));
                if (candidate.getDistance() != -1 && candidate.getDistance() < entry.getDistance()) {
                    entry.getBattleHex()->setRenderPathExit(true);
                    entry.getBattleHex()->setPathExit(Direction(i));
                    
                    candidate.getBattleHex()->setRenderPathEnterence(true);
                    candidate.getBattleHex()->setPathEnterence(getDirectionOpposite(Direction(i)));

                    currentLocation = currentLocation + getCubeCoord((Direction)i);
                    break;
                }

                if (i == NorthWest) {
                    return;
                }
            }
        } else {
            return;
        }
    }*/
}