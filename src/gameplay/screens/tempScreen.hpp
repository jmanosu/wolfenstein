#ifndef TEMPSCREEN
#define TEMPSCREEN

#include "gameplay/battle/battle.hpp"

#include "gameplay/screens/screen.hpp"

#include "objects/map/battleMap.hpp"

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