#include "mapUtils.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "objects/map/hexs/BattleHexs/landHex.hpp"
#include "objects/map/hexs/BattleHexs/waterHex.hpp"


namespace pt = boost::property_tree;

BattleHex * generateBattleHex(int);

BattleMap * JsonUtils::loadBattleMap(std::string file, TextureCache * textureCache)
{
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("assets/" + file);

    pt::ptree tree;
    pt::read_json(fullPath, tree);

    int rowNum = 0;
    int columnNum = 0;

    BattleMap * battleMap = new BattleMap();

    for (pt::ptree::value_type & row : tree.get_child("layout")) {
        for (pt::ptree::value_type & jsonHexIndex : row.second) {
            CubeCoord location = axialToCubeOddVertical(rowNum, columnNum);

            int type = jsonHexIndex.second.get<int>("");

            BattleHex * newHex = generateBattleHex(type);

            if (newHex != nullptr) {
                BattleTile * newLocation = new BattleTile();

                newLocation->setDepth(newHex->getDepth());
                newLocation->setHex(newHex);

                battleMap->setHexTile(location, newLocation->getDepth(), newLocation);
            }

            columnNum++;
        }
        rowNum++;
        columnNum = 0;
    }

    rowNum = 0;
    columnNum = 0;

    for (pt::ptree::value_type & row : tree.get_child("topography")) {
        for (pt::ptree::value_type & jsonHexIndex : row.second) {
            CubeCoord location = axialToCubeOddVertical(rowNum, columnNum);

            int depth = jsonHexIndex.second.get<int>("");

            BattleTile * tile = battleMap->getHexTile(location);

            if (tile != nullptr) {
                battleMap->setHexTileDepth(depth, tile);
            }

            columnNum++;
        }
        rowNum++;
        columnNum = 0;
    }

    
    return battleMap;
}

BattleHex * generateBattleHex(int id)
{
    switch (id) {
        case 0:
            {
                WaterHex * newHex = new WaterHex();
                return newHex;
            }
            break;
        case 1:
            {
                LandHex * newHex = new LandHex();
                newHex->setType(LandHex::LandHexType::grass);
                return newHex;
            }
            break;
        case 2:
            {
                LandHex * newHex = new LandHex();
                newHex->setType(LandHex::LandHexType::desert);
                return newHex;
            }
            break;
        case 3:
            {
                LandHex * newHex = new LandHex();
                newHex->setType(LandHex::LandHexType::snow);
                return newHex;
            }
            break;
        case 4:
            {
                return nullptr;
            }
            break;
        default:
            {
                return nullptr;
            }
            break;
    }
}