#ifndef HEXGRID_HPP
#define HEXGRID_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <list>
#include <tuple>

#include "geometry/cubeCoord.hpp"

template <typename Hex> class HexGrid {
    public:
        HexGrid();
        ~HexGrid();

        void add(CubeCoord, Hex);
        void erase(CubeCoord);

        Hex get(CubeCoord);

        typename std::map<CubeCoord, Hex>::iterator begin();
        typename std::map<CubeCoord, Hex>::iterator end();

    private:
        std::map<CubeCoord, Hex> mGrid;
};

template <class Hex> HexGrid<Hex>::HexGrid()
{

}

template <class Hex> HexGrid<Hex>::~HexGrid()
{
    for (typename std::pair<CubeCoord, Hex> pair : mGrid) {
        delete pair.second;
    }
}

template <class Hex> void HexGrid<Hex>::add(CubeCoord location, Hex hex)
{
    typename std::map<CubeCoord, Hex>::iterator it = mGrid.find(location);

    if (it != mGrid.end()) {
        delete mGrid[location];
        mGrid[location] = hex;
    } else {
        mGrid[location] = hex;
    }
}

template <class Hex> void HexGrid<Hex>::erase(CubeCoord location)
{
    typename std::map<CubeCoord, Hex>::iterator it = mGrid.find(location);

    if (it != mGrid.end()) {
        mGrid.erase(it);
    }
}

template <class Hex> Hex HexGrid<Hex>::get(CubeCoord location)
{
    typename std::map<CubeCoord, Hex>::iterator it = mGrid.find(location);

    if (it != mGrid.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

template <class Hex> typename std::map<CubeCoord, Hex>::iterator HexGrid<Hex>::begin()
{
    return mGrid.begin();
}

template <class Hex> typename std::map<CubeCoord, Hex>::iterator HexGrid<Hex>::end()
{
    return mGrid.end();
}

#endif