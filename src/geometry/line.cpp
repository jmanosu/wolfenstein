#include "line.hpp"

Line::Line() : Path(),
{

}

Line::Line(double x1, double y1, double x2, double y2) : Line(),
    mBegin(x1, y1),
    mEnd(x2, y2)
{


}

Line::~Line()
{

}

double Line::getOutput(double x)
{
    if (x < mLowerBound || x > mUpperBound) {
        mStatus = outOfBounds;
    }
}

GVector Line::getInterval(double scaler, int interval)
{
    GVector eigen = (mBegin + mEnd).Normalized();

    eigen.Scale(scaler * interval);

}