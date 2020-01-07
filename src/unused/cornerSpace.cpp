#include "cornerSpace.hpp"

CornerSpace::CornerSpace()
{

}

CornerSpace::~CornerSpace()
{

}

void CornerSpace::render()
{
    Graphics::instance()->setColor(0,0,0,1.0);
    Graphics::instance()->drawPoint(this->pos(world));
}

void CornerSpace::update()
{

}