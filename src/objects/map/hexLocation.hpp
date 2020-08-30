#ifndef HEXLOCATION_HPP
#define HEXLOCATION_HPP

#include "objects/gameEntity.hpp"

#include "geometry/cubeCoord.hpp"

template <typename Hex, typename HexObject> class HexTile : public GameEntity {
    public:
        HexTile();
        ~HexTile();

        CubeCoord getLocation();
        Hex * getHex();
        HexObject * getHexObject();

        void setLocation(CubeCoord location, int depth = 0);
        void setDepth(int);
        void setHex(Hex *);
        virtual void setHexObject(HexObject *);

        virtual void releaseHexObject();

        int getDepth();

        bool getHovered();
        bool getPressed();
        bool getClicked();

        void render();
        void update();

        enum Orientation {
            vertical = 0,
            horizontal
        };

    protected:
        CubeCoord _location;

        Orientation _orientation;

        int _width, _height, _peak, _depth;

        Hex * _hex;

        HexObject * _hexObject;
};

template <class Hex, class HexObject> HexTile<Hex, HexObject>::HexTile() :
    _orientation(vertical),

    _width(0),
    _height(0),
    _peak(0),
    _depth(0),

    _hex(nullptr),
    _hexObject(nullptr)
{

}

template <class Hex, class HexObject> HexTile<Hex, HexObject>::~HexTile()
{
    if (_hex != nullptr) {
        delete _hex;
    }

    if (_hexObject != nullptr) {
        delete _hexObject;
    }
}

template <class Hex, class HexObject> CubeCoord HexTile<Hex, HexObject>::getLocation()
{
    return _location;
}

template <class Hex, class HexObject> Hex * HexTile<Hex, HexObject>::getHex()
{
    return _hex;
}

template <class Hex, class HexObject> HexObject * HexTile<Hex, HexObject>::getHexObject()
{
    return _hexObject;
}

template <class Hex, class HexObject> void HexTile<Hex, HexObject>::setLocation(CubeCoord location, int depth)
{
    _location = location;
    _depth = depth;
}

template <class Hex, class HexObject> void HexTile<Hex, HexObject>::setDepth(int depth)
{
    _depth = depth;
}

template <class Hex, class HexObject> void HexTile<Hex, HexObject>::setHex(Hex * hex)
{
    _hex = hex;
    _hex->parent(this);
    _hex->setLocation(_location, _depth);

    if (_hexObject != nullptr) {
        _hexObject->setHex(hex);
    }
}

template <class Hex, class HexObject> void HexTile<Hex, HexObject>::setHexObject(HexObject * hexObject)
{
    if (_hexObject == nullptr && hexObject != nullptr) {
        _hexObject = hexObject;
        _hexObject->parent(this);
        _hexObject->setLocation(_location);
        _hexObject->setPlaced(true);
        _hexObject->setHex(_hex);
    }
}

template <class Hex, class HexObject> void HexTile<Hex, HexObject>::releaseHexObject()
{
    if (_hexObject != nullptr) {
        _hexObject->parent(nullptr);
        _hexObject = nullptr;
    }
}

template <class Hex, class HexObject> int HexTile<Hex, HexObject>::getDepth()
{
    return _depth;
}

template <class Hex, class HexObject> bool HexTile<Hex, HexObject>::getHovered()
{
    if (_hex->getHovered()) {
        return true;
    } else {
        return false;
    }
}

template <class Hex, class HexObject> bool HexTile<Hex, HexObject>::getClicked()
{
    if (_hex->getClicked()) {
        return true;
    } else {
        return false;
    }    
}

template <class Hex, class HexObject> bool HexTile<Hex, HexObject>::getPressed()
{
    if (_hex->getPressed()) {
        return true;
    } else {
        return false;
    }
}


template <class Hex, class HexObject> void HexTile<Hex, HexObject>::render()
{
    if (_hex != nullptr) {
        _hex->render();    
    }

    if (_hexObject != nullptr) {
        _hexObject->render();
    }
}

template <class Hex, class HexObject> void HexTile<Hex, HexObject>::update()
{
    if (_hex != nullptr) {
        _hex->update();
    }

    if (_hexObject != nullptr) {
        _hexObject->update();
    }
}

#endif