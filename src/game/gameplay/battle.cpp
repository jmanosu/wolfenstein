#include "battle.hpp"
#include "game/objects/hexs/landHex.hpp"
#include "graphics/textureCache.hpp"
#include "game/objects/units/mech.hpp"


Battle::Battle()
{

  TextureCache * textureCache = TextureCache::instance();

  textureCache->loadFile("textureFiles/test.json");


  mMap = new Map();

  std::vector<Hex *> bind;

  Hex templateHex;

  templateHex.setHighlightTexture(*(textureCache->getTexture("HighlightHex1")), NorthWest);
  templateHex.setHighlightTexture(*(textureCache->getTexture("HighlightHex2")), North);
  templateHex.setHighlightTexture(*(textureCache->getTexture("HighlightHex3")), NorthEast);
  templateHex.setHighlightTexture(*(textureCache->getTexture("HighlightHex4")), SouthEast);
  templateHex.setHighlightTexture(*(textureCache->getTexture("HighlightHex5")), South);
  templateHex.setHighlightTexture(*(textureCache->getTexture("HighlightHex6")), SouthWest);

  templateHex.setDimensions(horizontal, 43, 33, 13, 0);

  bind.push_back(new LandHex(templateHex, "GrassHex", "GroundSkirtHex"));
  bind.push_back(new LandHex(templateHex, "TreeHex", "GroundSkirtHex"));
  bind.push_back(new LandHex(templateHex, "DesertHex", "DesertSkirtHex"));
  bind.push_back(new LandHex(templateHex, "SnowHex", "GroundSkirtHex"));
  bind.push_back(new LandHex(templateHex, "WaterHex", "OceanSkirtHex"));
  bind.push_back(new LandHex(templateHex, "SnowForestHex", "GroundSkirtHex"));


  bind.at(1)->setLevel(4);
  bind.at(4)->setLevel(-4);
  
  std::vector<std::vector<int>> map {
    { 4,  4,  4,  0,  4,  4,  4},
    { 4,  4,  0,  2,  1,  4,  4},
    { 4,  0,  2,  2,  1,  0,  4},
    { 0,  4,  4,  0,  3,  3,  0},
    { 4,  4,  0,  3,  5,  0,  4},
    { 4,  4,  0,  0,  0,  4,  4},
    { 4,  4,  4,  0,  4,  4,  4}
  };


  mMap->loadMap(map, bind);


    tempPlayer = new Player();

    Mech * mech = new Mech();

    tempMechID = mech->id();

    tempPlayer->addUnit(mech);

    addPlayer(tempPlayer);

    addUnitToMap(CubeCoord(0,0), tempPlayer->getUnit(tempMechID));

    mMode = attack;
}

Battle::Battle(Map * map)
{
    mMap = map;
}

Battle::~Battle() {

}

void Battle::render()
{
    mMap->render();
    SDL_SetRenderDrawColor(Graphics::instance()->getRenderer(), 5, 42, 74, 255);
}

void Battle::update()
{
    mMap->update();

    InputManager * inputManager = InputManager::instance();
    for (int i = 0; i < inputManager->getKeyPressCount(); i++) {
        switch (inputManager->getKeyPress(i).sym)
        {
            case SDLK_0:
                {
                }
                break;        
            default:
                break;
        }
    }

    switch (mMode) {
        case placement:
            {
                Hex * selected = mMap->getClickedHex();
                if (selected != nullptr) {
                    mMap->moveHexObject(selected->getLocation(), tempMechID);
                }
            }
            break;
        case attack:
            {
                Hex * clickedHex = mMap->getClickedHex();
                if (clickedHex != nullptr) {
                    mMap->applyWeapon(new Weapon(), clickedHex->getLocation(), clickedHex->getLocation());
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
    mMap->addHexObject(location, unit);
}