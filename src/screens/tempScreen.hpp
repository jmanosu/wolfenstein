#ifndef TEMPSCREEN
#define TEMPSCREEN

#include "screens/screen.hpp"
#include "game/objects/map.hpp"

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