#ifndef HEXGRID_HPP
#define HEXGRID_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <list>
#include <tuple>

#include "geometry/cubeCoord.hpp"

template <typename Index> class HexGrid2 {
    public:
        HexGrid2();
        ~HexGrid2();

        void set(CubeCoord, Index *);
        void erase(CubeCoord);

        Index * get(CubeCoord);

        typename std::map<CubeCoord, Index *>::iterator begin();
        typename std::map<CubeCoord, Index *>::iterator end();

    private:
        std::map<CubeCoord, Index *> mGrid;
};

template <class Index> HexGrid2<Index>::HexGrid2()
{

}

template <class Index> HexGrid2<Index>::~HexGrid2()
{

}

template <class Index> void HexGrid2<Index>::set(CubeCoord location, Index * hex)
{
    typename std::map<CubeCoord, Index *>::iterator it = mGrid.find(location);

    if (it != mGrid.end()) {
        delete mGrid[location];
        mGrid[location] = hex;
    } else {
        mGrid[location] = hex;
    }
}

template <class Index> void HexGrid2<Index>::erase(CubeCoord location)
{
    typename std::map<CubeCoord, Index *>::iterator it = mGrid.find(location);

    if (it != mGrid.end()) {
        mGrid.erase(it);
    }
}

template <class Index> Index * HexGrid2<Index>::get(CubeCoord location)
{
    typename std::map<CubeCoord, Index *>::iterator it = mGrid.find(location);

    if (it != mGrid.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

template <class Index> typename std::map<CubeCoord, Index *>::iterator HexGrid2<Index>::begin()
{
    return mGrid.begin();
}

template <class Index> typename std::map<CubeCoord, Index *>::iterator HexGrid2<Index>::end()
{
    return mGrid.end();
}

template <typename Index> class HexGrid {
    public:
        HexGrid();
        ~HexGrid();

        void add(CubeCoord, Index);
        void erase(CubeCoord);

        Index get(CubeCoord);

        typename std::map<CubeCoord, Index>::iterator begin();
        typename std::map<CubeCoord, Index>::iterator end();

    private:
        std::map<CubeCoord, Index> mGrid;
};

template <class Index> HexGrid<Index>::HexGrid()
{

}

template <class Index> HexGrid<Index>::~HexGrid()
{
    for (typename std::pair<CubeCoord, Index> pair : mGrid) {
        delete pair.second;
    }
}

template <class Index> void HexGrid<Index>::add(CubeCoord location, Index hex)
{
    typename std::map<CubeCoord, Index>::iterator it = mGrid.find(location);

    if (it != mGrid.end()) {
        delete mGrid[location];
        mGrid[location] = hex;
    } else {
        mGrid[location] = hex;
    }
}

template <class Index> void HexGrid<Index>::erase(CubeCoord location)
{
    typename std::map<CubeCoord, Index>::iterator it = mGrid.find(location);

    if (it != mGrid.end()) {
        mGrid.erase(it);
    }
}

template <class Index> Index HexGrid<Index>::get(CubeCoord location)
{
    typename std::map<CubeCoord, Index>::iterator it = mGrid.find(location);

    if (it != mGrid.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

template <class Index> typename std::map<CubeCoord, Index>::iterator HexGrid<Index>::begin()
{
    return mGrid.begin();
}

template <class Index> typename std::map<CubeCoord, Index>::iterator HexGrid<Index>::end()
{
    return mGrid.end();
}


#endif