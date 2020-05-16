#include "widget.hpp"

Widget::Widget() :
    mMargin(0),
    mBorder(0),
    mPadding(0),
    mHovered(false),
    mClicked(false)
{
    mContentBox.parent(this);
}

Widget::~Widget()
{

}

void Widget::render()
{
    for (Widget * it : mChildren) {
        delete it;
    }

}

void Widget::update()
{
    InputManager * inputManager = InputManager::instance();

    bool mouseCollision = mContentBox.collision(inputManager->getMouseX(), inputManager->getMouseY());

    if (mouseCollision == true) {
        mHovered = true;

        if (inputManager->mousePress(SDL_BUTTON_LEFT)) {
            mClicked = true;
        } else {
            mClicked = false;
        }

    } else {
        mHovered = false;
        mClicked = false;
    }
}

void Widget::setHeight(int height)
{
    mContentBox.setHeight(height);
}

void Widget::setWidth(int width)
{
    mContentBox.setWidth(width);
}

void Widget::setPadding(int padding)
{
    mPadding = padding;
}

void Widget::setBorder(int border)
{
    mBorder = border;
}

bool Widget::hovered()
{
    return mHovered;
}

bool Widget::clicked()
{
    return mClicked;
}

void Widget::addChild(Widget * widget, int index)
{
    if (index != -1) {
        mChildren.insert(mChildren.begin() + index, widget);
    } else {
        mChildren.push_back(widget);
    }
}