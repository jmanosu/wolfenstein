#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "game/objects/map.hpp"
#include "game/gameplay/battle.hpp"
#include "game/player/player.hpp"

enum BATTLEMODE {
    placement = 0,
    attack
};

class Battle : GameEntity {
    public:
        Battle();
        Battle(Map *);
        ~Battle();

        void render();
        void update();

        void addPlayer(Player *);

        void addUnitToMap(CubeCoord, Unit *);
    private:
        Map * mMap;
        std::vector<Player *> mPlayers;

        BATTLEMODE mMode;

        ID tempMechID;
        Player * tempPlayer;
};

#endif