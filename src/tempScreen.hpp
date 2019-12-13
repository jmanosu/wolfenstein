#ifndef TEMPSCREEN
#define TEMPSCREEN

#include "screen.hpp"
#include "map.hpp"

class TempScreen : public Screen {
    public:
        TempScreen();
        ~TempScreen();

        void render();
        void update();

    private:
        Map * mMap;
};

#endif