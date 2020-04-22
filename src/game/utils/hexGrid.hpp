#ifndef HEXGRID_HPP
#define HEXGRID_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <list>
#include <tuple>

#include "game/utils/cubeCoord.hpp"

template <typename Hex> class HexGrid {
    public:
        HexGrid();
        ~HexGrid();

        void addHex(CubeCoord, Hex *);
        Hex * getHex(CubeCoord);
    private:
        std::map<CubeCoord, Hex *> mGrid;
};

#endif