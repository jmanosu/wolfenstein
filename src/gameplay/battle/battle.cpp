#include "battle.hpp"

#include "graphics/textureCache.hpp"

#include "objects/map/hexObjects/units/mech.hpp"

#include "objects/map/mapUtils.hpp"

#include "graphics/graphicUtils.hpp"

#include "geometry/line.hpp"


Battle::Battle()
{

    TextureCache * textureCache = TextureCache::instance();

    GraphicUtils::loadTextureFile("textureFiles/test.json", textureCache);

    mMap = JsonUtils::loadBattleMap("maps/test.json", textureCache);

    tempPlayer = new Player();

    Mech * mech = new Mech();

    tempMechID = mech->id();

    tempPlayer->addUnit(mech);

    tempButton = new Button();
    tempButton->setWidth(100);
    tempButton->setHeight(100);
    tempButton->pos(GVector(10,0));

    addPlayer(tempPlayer);

    addUnitToMap(CubeCoord(0,0), tempPlayer->getUnit(tempMechID));

    mMode = attack;

    mSelectedUnit = nullptr;
    mSelectedWeapon = nullptr;

    mPathTexture.setPath(new Line(1,50));
    mPathTexture.setLowerX(80);
    mPathTexture.setUpperX(300);
    mPathTexture.setDX(40);
    mPathTexture.setTexture(Texture("animatedDot.png"));
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
    tempButton->update();
    InputManager * inputManager = InputManager::instance();

    if (inputManager->keyRelease(SDLK_1)) {
        std::cout << "BATTLE - setting mode to placement" << std::endl;
        mMode = placement;
    } else if (inputManager->keyRelease(SDLK_2)) {
        std::cout << "BATTLE - setting mode to attack" << std::endl;
        mMode = attack;
    } else if (inputManager->keyRelease(SDLK_3)) {
        std::cout << "BATTLE - setting mode to effect" << std::endl;
        mMode = effect;
    } else if (inputManager->keyRelease(SDLK_4)) {
        std::cout << "BATTLE - setting mode to move" << std::endl;
        mMode = move;        
    } else if (inputManager->keyRelease(SDLK_5)) {
        
    } else if (inputManager->keyRelease(SDLK_6)) {
        
    }

    if (tempButton != nullptr && tempButton->clicked()) {
        std::cout << "button has been clicked" << std::endl;
    }

    switch (mMode) {
        case placement:
            {

                BattleHex * selected = mMap->getClickedHex();
                if (selected != nullptr) {
                        tempHexCollection.setHighlight(false);
                        tempHexCollection = mMap->getHexReachableCollection(4, selected->getLocation());
                        tempHexCollection.setHighlight(true);
//                    mMap->modifyHexReachable(2, selected->getLocation(), [&](BattleHex * hex) {
//                        std::cout << "test" << std::endl;
//                    });
//                    mMap->moveHexObject(selected->getLocation(), tempMechID);
                }
            }
            break;
        case attack:
            {
                BattleHex * clickedHex = mMap->getClickedHex();
                if (clickedHex != nullptr) {
                    if (mSelectedWeapon != nullptr) {
                        mMap->applyWeapon(mSelectedWeapon, clickedHex->getLocation(), clickedHex->getLocation());
                        mSelectedWeapon = nullptr;
                    } else {
                        HexObject * hexObject = clickedHex->getHexObject();
                        if (hexObject != nullptr) {
                            Unit * unit = mMap->getUnit(hexObject->id());
                            if (unit != nullptr) {
                                std::cout << "UNIT: " << unit->id() << std::endl;
                                mSelectedWeapon = unit->getWeapon();
                            }
                        }                   

                    }
                }
            }
            break;
        case effect:
            {
                BattleHex * selected = mMap->getClickedHex();
                if (selected != nullptr) {
                    tempHexCollection.drawPath(selected->getLocation());
                }
            }
            break;
        case move:
            {
                BattleHex * selected = mMap->getClickedHex();
                if (selected != nullptr) {
                    if (mSelectedUnit == nullptr) {
                        mSelectedUnit = mMap->getHexObject(selected->getLocation());
                    } else {
                        mMap->moveHexObject(selected->getLocation(), mSelectedUnit->id());
                        mSelectedUnit = nullptr;
                    }
                }
            }
            break;
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