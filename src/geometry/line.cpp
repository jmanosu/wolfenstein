#include "line.hpp"

#include "graphics/graphics.hpp"

Line::Line() : Path()
{

}

Line::Line(double x1, double y1, double x2, double y2) : Line()
{
    pos(GVector(x1, y1));

    mEnd.x = x2 - x1;
    mEnd.y = y2 - y1;
}

Line::~Line()
{

}

double Line::getOutput(double x)
{
}

GVector Line::getInterval(double scaler, int interval)
{
    GVector eigen = mEnd.Normalized();

    eigen.Scale(scaler * interval);

    eigen = eigen + pos(world);

    if (eigen.x > mEnd.x || eigen.y > mEnd.y) {
        mStatus = outOfBounds;
    }

    return eigen;
}

void Line::render()
{
    Graphics * mGraphics = Graphics::instance();
    mGraphics->setColor(255,0,0);
//    mGraphics->drawRectangle(pos(world).x, mBegin.y, mEnd.x, mEnd.y, true);
    mGraphics->setColor(0,0,0);

}

void Line::render(Texture * texture, int interval)
{
    if (texture == nullptr) {
        return;
    }

    for (int i = 0; i * interval < mEnd.Magnitude(); i++) {
        GVector pos = getInterval(interval, i);

        texture->render(pos);
    }
}

void Line::setStart(GVector begin)
{
    GVector position = pos(world);

    mEnd = mEnd + position - begin;

    pos(begin);
}

void Line::setEnd(GVector end, SPACE space)
{
    if (space == local) {
        mEnd = end;
    } else {
        mEnd = end - pos(world);
    }
}