#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "objects/interactableEntity.hpp"

#include "geometry/boundingBox.hpp"

#include "gameplay/input/inputManager.hpp"

class Widget : public InteractableEntity {
    public:
        Widget();
        ~Widget();

        void render();
        void update();

        void setWidth(int);
        void setHeight(int);
        void setPadding(int);
        void setMargin(int);
        void setBorder(int);

        bool hovered();
        bool clicked();

        void addChild(Widget *, int = -1);
    protected:
        BoundingBox mContentBox;

        int mMargin, mBorder, mPadding;

        bool mHovered, mClicked;

        std::vector<Widget *> mChildren;

        
// possible future use
//        int mPaddingTop, mPaddingBottom, mPaddingRight, mPaddingLeft;
//        int mMarginTop, mMarginBottom, mMarginRight, mMarginLeft;
//        int mBorderTop, mBorderBottom, mBorderRight, mBorderLeft; 

};

#endif