#include "button.hpp"
#include "graphics/graphics.hpp"

Button::Button()
{
}

Button::~Button()
{

}

void Button::render()
{
    Graphics * graphics = Graphics::instance();

    GVector position = pos(world);

    graphics->drawRectangle(position.x - mContentBox.getWidth() / 2, position.y - mContentBox.getHeight() / 2, mContentBox.getWidth(), mContentBox.getHeight(), true);
}

void Button::update()
{
    Widget::update();
}