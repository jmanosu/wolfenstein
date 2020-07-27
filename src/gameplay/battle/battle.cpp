#include "battle.hpp"

#include "graphics/textureCache.hpp"

#include "objects/map/hexObjects/units/mech.hpp"

#include "objects/map/mapUtils.hpp"

#include "graphics/graphicUtils.hpp"

#include "geometry/line.hpp"


Battle::Battle() :
    _currentPlayer(nullptr),

    _selectedUnit(nullptr)
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
    SDL_SetRenderDrawColor(Graphics::instance()->getRenderer(), 200, 200, 74, 255);
    tempButton->render();
    SDL_SetRenderDrawColor(Graphics::instance()->getRenderer(), 5, 42, 74, 255);
    mPathTexture.render();
}

void Battle::update()
{
    mMap->update();

    InputManager * inputManager = InputManager::instance();

    switch (_mode)
    {
        case setup:
            {
                BattleTile * selected = mMap->getClickedTile();

                if (selected != nullptr && _startRegion.checkEntry(selected->getLocation()) && _selectedUnit != nullptr && !_selectedUnit->getPlaced()) {
                    std::cout << "valid start" << std::endl;
                    mMap->setHexObject(selected->getLocation(), _selectedUnit);
                    _selectedUnit = nullptr;

                    // delete later
                    _selectedUnit = _currentPlayer->getUnplacedUnit();

                    if (_selectedUnit == nullptr) {
                        setMode(battle);
                    }
                }
            }
            break;
        case battle:
            {
                BattleTile * selected = mMap->getClickedTile();

                if (selected != nullptr && _selectedUnit == nullptr) {
                    _selectedUnit = selected->getUnit();
                } else if (selected != nullptr && _selectedUnit != nullptr) {
                    if (_selectedUnit->getLocation() != selected->getLocation()) {
                        mMap->moveHexObject(_selectedUnit->getLocation(), selected->getLocation());
                    }
                }
            }
        default:
            break;
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