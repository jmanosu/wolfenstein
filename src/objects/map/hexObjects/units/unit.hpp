#ifndef UNITS_HPP
#define UNITS_HPP

#include "objects/map/hexObjects/hexObject.hpp"

class Unit : public HexObject {
    public:
        Unit();
        ~Unit();

        void setWeaponId(int);
        int getWeaponId();

        void reset();

        void setHealth(int);
        int getHealth();
        
        void setMoveRange(int);
        int getMoveRange();

        void setMoveCount(int);
        int getMoveCount();

        bool isMovable();

        struct GameStats {
            int _health;
            int _moveRange;
            int _moveCount;
        };

        struct RenderMode {
            bool highlight;
        };
    protected:
        int _weaponId;

        GameStats _defaultGameStats;
        GameStats _currentGameStats;
};

#endif