#include "space.hpp"

Space::Space()
{

}

Space::~Space()
{

}

void Space::render()
{
    Graphics::instance()->setColor(0,0,0,1.0);
    Graphics::instance()->drawPoint(this->pos(world));
}

void Space::update()
{

}