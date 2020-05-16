#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "objects/widgets/widget.hpp"
#include "graphics/graphics.hpp"

class Button : public Widget {
    public:
        Button();
        ~Button();

        void render();
        void update();

    private:
};

#endif