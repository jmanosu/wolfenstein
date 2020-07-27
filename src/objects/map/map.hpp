/*
File: map.hpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header file for map. Map has a 3 dimensional array of wall objects
  called floors. This allows for multipule levels.

*/
#ifndef Map_hpp
#define Map_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <list>
#include <tuple>

#include "objects/gameEntity.hpp"
#include "objects/map/hexGrid.hpp"
#include "objects/map/hexs/hex.hpp"
#include "objects/map/hexObjects/hexObject.hpp"
#include "objects/map/weapons/weapon.hpp"

#include "geometry/cubeCoord.hpp"

#include "utils/constants.hpp"

#include "gameplay/input/inputManager.hpp"

#include "graphics/textures/animatedTexture.hpp"

#include "objects/map/hexLocation.hpp"

template <class HexTile> class HexMap : public GameEntity {
  public:
    HexMap();
    ~HexMap();

    void render();
    void update();

    HexTile * getHexTile(CubeCoord);

    HexTile * generateHexTile(CubeCoord location, int depth = 0);
    
    void setHexTile(CubeCoord location, int depth, HexTile * tile);
    void setHexTileLocation(CubeCoord, HexTile *);
    void setHexTileDepth(int, HexTile *);

    void setNeighbors(CubeCoord);

    HexTile * getPressedTile();
    HexTile * getHoveredTile();
    HexTile * getClickedTile();

    CubeCoord getDirection(HexSide);

    enum TileOrientation {
      vertical = 0,
      horizontal = 1
    };

  protected:
    HexGrid2<HexTile> _HexGrid;

    HexTile * _selectedTile;
    HexTile * _hoveredTile;
    HexTile * _clickedTile;

    TileOrientation _tileOrientation;

    int _width, _height, _peak;

    int _depthDefault = 3;
};

template <class HexTile> HexMap<HexTile>::HexMap() : GameEntity(),
  _selectedTile(nullptr),
  _hoveredTile(nullptr),
  _clickedTile(nullptr),

  _tileOrientation(TileOrientation::horizontal),

  _width(43),
  _height(33),
  _peak(13)
{
  scale(GVector(3,3));
  pos(GVector(300,300));
}

template <class HexTile> HexMap<HexTile>::~HexMap()
{
  for(typename std::pair<const CubeCoord, HexTile *> & hexTile : _HexGrid) {
    delete hexTile.second;
  }
}

template <class HexTile> void HexMap<HexTile>::render()
{
  for(typename std::pair<const CubeCoord, HexTile *> & hexTile : _HexGrid) {
    hexTile.second->render();
  }
}

template <class HexTile> void HexMap<HexTile>::update()
{
  _hoveredTile = nullptr;
  _clickedTile = nullptr;
  _selectedTile = nullptr;
  
  for(typename std::pair<const CubeCoord, HexTile *> & hexTile : _HexGrid) {
    hexTile.second->update();

    if (hexTile.second->getHovered()) {
      _hoveredTile = hexTile.second;
    }

    if (hexTile.second->getClicked()) {
      _clickedTile = hexTile.second;
    }

    if (hexTile.second->getPressed()) {
      _selectedTile = hexTile.second;
    }
  }
}

template <class HexTile> HexTile * HexMap<HexTile>::getHexTile(CubeCoord location)
{
  return _HexGrid.get(location);
}

template <class HexTile> HexTile * HexMap<HexTile>::generateHexTile(CubeCoord location, int depth)
{
  HexTile * hexTile = _HexGrid.get(location);
  if (hexTile == nullptr) {
    hexTile = new HexTile();
    setHexTile(location, depth, hexTile);
    return hexTile;
  }
}

template <class HexTile> void HexMap<HexTile>::setHexTile(CubeCoord location, int depth, HexTile * hexTile)
{
  hexTile->parent(this);
  hexTile->setLocation(location);
  hexTile->setDepth(0);

  _HexGrid.set(location, hexTile);

  setHexTileLocation(location, hexTile);
  setHexTileDepth(depth, hexTile);

  setNeighbors(location);
}

template <class HexTile> void HexMap<HexTile>::setHexTileLocation(CubeCoord location, HexTile * hexTile)
{
  int x = location.getX();
  int z = location.getZ();

  if (_tileOrientation == TileOrientation::vertical) {
    GVector newPos;

    newPos.x = (_width - 1) * x + _width / 2 * z;
    newPos.y = (_height - _peak - 1)  * z;

    hexTile->pos(newPos);
  } else {
    GVector newPos;

    newPos.x = (_width - _peak - 1)  * x;
    newPos.y = (z + (x - (x & 1)) / 2 - 1) * (_height - 1) + (_height / 2) * (x % 2);

    hexTile->pos(newPos);
  }
}

template <class HexTile> void HexMap<HexTile>::setHexTileDepth(int depth, HexTile * tile)
{
  GVector newPos = tile->pos(local);

  newPos.y -= tile->getDepth() * _depthDefault + depth * _depthDefault;

  tile->pos(newPos);

  tile->setDepth(depth);
}

template <class HexTile> void HexMap<HexTile>::setNeighbors(CubeCoord location)
{
  HexTile * hexTile = getHexTile(location);

  for (HexSide i = 0; i < 6; i++) {      
    CubeCoord neighborLocation = location + getDirection(i);
    HexTile * neighborHexTile = getHexTile(neighborLocation);

    if(neighborHexTile != nullptr) {
      neighborHexTile->setNeighbor((i + 3) % 6, hexTile);
    }

    if (hexTile != nullptr) {
      hexTile->setNeighbor(i, neighborHexTile);
    }
  }
}

template <class HexTile> HexTile * HexMap<HexTile>::getPressedTile()
{
  return _selectedTile;
}

template <class HexTile> HexTile * HexMap<HexTile>::getHoveredTile()
{
  return _hoveredTile;
}

template <class HexTile> HexTile * HexMap<HexTile>::getClickedTile()
{
  return _clickedTile;
}

template <class HexTile> CubeCoord HexMap<HexTile>::getDirection(HexSide side)
{
  switch (side)
  {
    case 0:
      return CubeCoord(0, -1);
      break;
    case 1:
      return CubeCoord(1, -1);
      break;
    case 2:
      return CubeCoord(1, 0);
      break;
    case 3:
      return CubeCoord(0, 1);
      break;
    case 4:
      return CubeCoord(-1, 1);
      break;
    case 5:
      return CubeCoord(-1, 0);
      break;
    default:
      return CubeCoord(0, 0);
      break;
  }
}

#endif