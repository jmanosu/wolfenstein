/*
File: cubeCoord.hpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header function for CubeCoord
*/
#ifndef CUBECOORD_HPP
#define CUBECOORD_HPP

#include <iostream>
#include <map>

class CubeCoord
{
    private:
    int x;
    int y;
    int z;

    public:

    CubeCoord() : x(0), y(0), z(0) {}
    CubeCoord(int _q, int _r) : x(_q), y(-_q - _r), z(_r) {}

    friend CubeCoord operator+(const CubeCoord & lhs, const CubeCoord & rhs);
    friend CubeCoord operator-(const CubeCoord & lhs, const CubeCoord & rhs);
    friend bool operator<(const CubeCoord & lhs, const CubeCoord & rhs);

    int getX() const { return x; }
    int getY() const { return y; }
    int getZ() const { return z; }
    int getQ() const { return x; }
    int getR() const { return z; }
    
    void set(int _q, int _r);
};


enum Direction {
  North = 0,
  NorthEast,
  SouthEast,
  South,
  SouthWest,
  NorthWest
};

CubeCoord getCubeCoord(Direction direction);
Direction getDirection(CubeCoord lhs, CubeCoord rhs);

CubeCoord axialToCubeOddHorizontal(int row, int column);
CubeCoord axialToCubeEvenHorizontal(int row, int column);
CubeCoord axialToCubeOddVertical(int row, int column);
CubeCoord axialToCubeEvenVertical(int row, int column);

#endif