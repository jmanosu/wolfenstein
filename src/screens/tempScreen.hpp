#ifndef TEMPSCREEN
#define TEMPSCREEN

#include "screens/screen.hpp"
#include "game/objects/map.hpp"
#include "game/gameplay/battle.hpp"

class TempScreen : public Screen {
    public:
        TempScreen();
        ~TempScreen();

        void render();
        void update();
        void load();
    private:
        Battle * mBattle;
};

#endif