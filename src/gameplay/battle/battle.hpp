#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "objects/map/battleMap.hpp"

#include "gameplay/players/player.hpp"

#include "objects/widgets/button.hpp"

enum BATTLEMODE {
    placement = 0,
    attack,
    effect,
    move
};

class Battle : GameEntity {
    public:
        Battle();
        Battle(BattleMap *);
        ~Battle();

        void render();
        void update();

        void addPlayer(Player *);

        void addUnitToMap(CubeCoord, Unit *);
    private:
        BattleMap * mMap;
        std::vector<Player *> mPlayers;

        BATTLEMODE mMode;

        ID tempMechID;
        Player * tempPlayer;

        HexObject * mSelectedUnit;

        Weapon * mSelectedWeapon;

        Button * tempButton;
};

#endif