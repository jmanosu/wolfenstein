#include "battle.hpp"

#include "graphics/textureCache.hpp"

#include "objects/map/hexObjects/units/mech.hpp"

#include "objects/map/mapUtils.hpp"

#include "graphics/graphicUtils.hpp"

#include "geometry/line.hpp"


Battle::Battle() :
    _currentPlayer(nullptr),

    _selectedUnit(nullptr),
    _selectedHexObject(nullptr)
{

    TextureCache * textureCache = TextureCache::instance();

    GraphicUtils::loadTextureFile("textureFiles/test.json", textureCache);

    mMap = JsonUtils::loadBattleMap("maps/test.json", textureCache);

    tempPlayer = new Player();

    Mech * mech = new Mech();

    tempPlayer->addUnit(mech);

    mech = new Mech();

    tempPlayer->addUnit(mech);

    mech = new Mech();

    tempPlayer->addUnit(mech);


    _selectedUnit = mech;

    tempButton = new Button();
    tempButton->setWidth(100);
    tempButton->setHeight(100);
    tempButton->pos(GVector(10,0));

    addPlayer(tempPlayer);

    _mode = battle;

    mSelectedUnit = nullptr;
    mSelectedWeapon = nullptr;

    Texture texture("development/random/circle.png");

    texture.scale(GVector(2,2));
    

    mPathTexture.setPath(new Line(0, 0, 400, 400));
    mPathTexture.setTexture(texture);

    texturePathToggle = false;

    /* for real stuff */
    _selectedTile = nullptr;
    _previousSelectedTile = nullptr;

    _startRegion = mMap->getHexRangeCollection(3, CubeCoord(0,0));

    setMode(setup);
}

Battle::Battle(BattleMap * map)
{
    mMap = map;
}

Battle::~Battle() {

}

void Battle::render()
{
    mMap->render();
    mPathTexture.render();
}

void Battle::update()
{
    mMap->update();

    InputManager * inputManager = InputManager::instance();

    if (inputManager->mouseRelease(SDL_BUTTON(SDL_BUTTON_LEFT))) {
        handleSelectedTile(mMap->getClickedTile());
    }
}

void Battle::addPlayer(Player * player)
{
    mPlayers.push_back(player);
}

void Battle::addUnitToMap(CubeCoord location, Unit * unit)
{
    mMap->addUnit(location, unit);
}

void Battle::setMode(BATTLEMODE mode)
{
    switch (mode)
    {
        case setup:
            {
                _startRegion.setHighlight(true);

                _currentPlayer = mPlayers.at(0);

            }
            break;   
        case battle:
            {
                _startRegion.setHighlight(false);
            }
            break;
        default:
            break;
    }

    _mode = mode;
}

void Battle::setSelectedTile(BattleTile * tile)
{
    setSelectedUnit(nullptr);
    setSelectedHexObject(nullptr);

    _previousSelectedTile = _selectedTile;
    _selectedTile = tile;

    if (_selectedTile != nullptr) {
        switch (_selectedTile->getHexObjectType())
        {
            case BattleTile::HexObjectType::hexObject:
                {  
                    HexObject * hexObject = _selectedTile->getHexObject();
                    setSelectedHexObject(hexObject);
                }
                break;
            case BattleTile::HexObjectType::unit:
                {
                    Unit * unit = _selectedTile->getUnit();
                    setSelectedUnit(unit);
                }
                break;
            case BattleTile::HexObjectType::none:
                {

                }
                break;        
            default:
                break;
        }
    }
}

void Battle::setSelectedHexObject(HexObject * hexObject)
{
    _selectedHexObject = hexObject;
}

void Battle::setSelectedUnit(Unit * unit)
{
    _selectedUnit = unit;

    _highlightedRegion.setHighlight(false);


    if (_selectedUnit != nullptr) {
        if (_selectedUnit->getMoveCount() > 0) {
            _highlightedRegion = mMap->getHexRangeCollection(_selectedUnit->getMoveRange(), _selectedUnit->getLocation());
            _highlightedRegion.setHighlight(true);
        }
    }
}

void Battle::handleSelectedTile(BattleTile * tile)
{
    switch (_mode) {
        case setup:
            {
                if (tile != nullptr) {
                    if (_startRegion.checkEntry(tile->getLocation()) && _selectedUnit != nullptr && !_selectedUnit->getPlaced()) {
                        if (tile->getUnit() != nullptr) {
                            std::cout << "swaping" << std::endl;
                            Unit * selectedUnit = tile->getUnit();
                            selectedUnit->setPlaced(false);

                            tile->releaseHexObject();
                            tile->setHexObject(_selectedUnit);

                            _selectedUnit = selectedUnit;
                        } else {
                            std::cout << "valid start" << std::endl;

                            mMap->setHexObject(tile->getLocation(), _selectedUnit);

                            // delete later
                            _selectedUnit = _currentPlayer->getUnplacedUnit();

                            if (_selectedUnit == nullptr) {
                                setMode(battle);
                            }
                        }
                    }
                }
            }
            break;
        case battle:
            {
                if (_selectedTile != nullptr) {
                    if (_selectedUnit != nullptr && tile != nullptr && _selectedUnit->isMovable() && _highlightedRegion.checkEntry(tile->getLocation()) && _selectedUnit->getLocation() != tile->getLocation()) {
                        mMap->moveHexObject(_selectedUnit->getLocation(), tile->getLocation());
                        _selectedUnit->setMoveCount(_selectedUnit->getMoveCount() - 1);
                    }
                }

                if (tile != nullptr) {
                    setSelectedTile(tile);
                }
            }
        default:
            break;
    }
}