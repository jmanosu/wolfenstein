#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "objects/map/battleMap.hpp"

#include "gameplay/players/player.hpp"

#include "objects/widgets/button.hpp"

#include "graphics/textures/texturePath.hpp"

class Battle : GameEntity {
    public:
        Battle();
        Battle(BattleMap *);
        ~Battle();

        enum BATTLEMODE {
            setup = 0,
            battle,
            effect,
            move,
            path
        };

        void render();
        void update();

        void addPlayer(Player *);

        void addUnitToMap(CubeCoord, Unit *);

        void setMode(BATTLEMODE);

        void setSelectedTile(BattleTile *);

        void setSelectedHexObject(HexObject *);
        void setSelectedUnit(Unit *);

        void handleSelectedTile(BattleTile *);

    private:

        ID tempMechID;
        Player * tempPlayer;

        HexObject * mSelectedUnit;

        Weapon * mSelectedWeapon;

        Button * tempButton;

        HexCollection tempHexCollection;

        TexturePath  mPathTexture;
        bool texturePathToggle;

        HexCollection _selectedUnitRegion;

        HexCollection _startRegion;

        /* for real member varaibles */
        BattleMap * mMap;

        std::vector<Player *> mPlayers;
        Player * _currentPlayer;

        BATTLEMODE _mode;

        HexCollection _highlightedRegion;

        BattleTile * _selectedTile;
        BattleTile * _previousSelectedTile;
        Unit * _selectedUnit;
        HexObject * _selectedHexObject;
};

#endif