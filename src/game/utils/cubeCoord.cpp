#include "cubeCoord.hpp"

CubeCoord operator+(const CubeCoord & lhs, const CubeCoord & rhs)
{
    return CubeCoord(lhs.getX() + rhs.getX(), lhs.getZ() + rhs.getZ());
}

bool operator<(const CubeCoord & lhs, const CubeCoord & rhs)
{

    if(lhs.getZ() < rhs.getZ()) return true;
    if(lhs.getZ() > rhs.getZ()) return false;

    if(lhs.getX() < rhs.getX()) return true;
    if(lhs.getX() > rhs.getX()) return false;

    return false;
}

void CubeCoord::set(int _q, int _r)
{
    x = _q;
    y = -_q - _r;
    z = _r;
}

CubeCoord getCubeCoord(Direction direction) {
    switch (direction) {
    case North:
        return CubeCoord(0, -1);
        break;    
    case NorthEast:
        return CubeCoord(1, -1);
        break;
    case SouthEast:
        return CubeCoord(1, 0);
        break;
    case South:
        return CubeCoord(0, 1);
        break;
    case SouthWest:
        return CubeCoord(-1, 1);
        break;
    case NorthWest:
        return CubeCoord(-1, 0);
        break;
    default:
        return CubeCoord(0, 0);
        break;
    }
}

CubeCoord axialToCubeOddHorizontal(int row, int column)
{
    int q = column - (row - (row&1)) / 2;
    int r = row;
    return CubeCoord(q, r);
}

CubeCoord axialToCubeEvenHorizontal(int row, int column)
{
    int q = column - (row + (row&1)) / 2;
    int r = row;
    return CubeCoord(q, r);
}

CubeCoord axialToCubeOddVertical(int row, int column)
{
    int q = column;
    int r = row - (column - (column&1)) / 2;
    return CubeCoord(q, r);
}

CubeCoord axialToCubeEvenVertical(int row, int column)
{
    int q = column;
    int r = row - (column + (column&1)) / 2;
    return CubeCoord(q, r);
}