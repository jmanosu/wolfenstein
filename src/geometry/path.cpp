#include "path.hpp"

Path::Path() :
    mLowerBound(0),
    mUpperBound(0),
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

void Path::setLowerBound(double lowerBound)
{
    mLowerBound = lowerBound;
}

void Path::setUppderBound(double upperBound)
{
    mUpperBound = upperBound;
}

double Path::getLowerBound()
{
    return mLowerBound;
}

double Path::getUpperBound()
{
    return mUpperBound;
}