#include "path.hpp"

Path::Path() :
    mStatus(valid)
{

}

Path::~Path()
{

}

double Path::getOutput(double)
{
    return 0;
}

PathStatus Path::getStatus()
{
    return mStatus;
}