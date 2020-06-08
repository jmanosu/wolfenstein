#include "mapUtils.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

BattleHex * decodeHex(pt::ptree::value_type *, TextureCache *);

BattleMap * JsonUtils::loadBattleMap(std::string file, TextureCache * textureCache)
{
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("assets/" + file);

    pt::ptree tree;
    pt::read_json(fullPath, tree);

    std::vector<BattleHex *> hexs;

    for (pt::ptree::value_type & hex : tree.get_child("hexs")) {
        hexs.push_back(decodeHex(&hex, textureCache));
    }

    int rowNum = 0;
    int columnNum = 0;

    BattleMap * battleMap = new BattleMap();

    for (pt::ptree::value_type & row : tree.get_child("layout")) {
        for (pt::ptree::value_type & jsonHexIndex : row.second) {
            CubeCoord location = axialToCubeOddVertical(rowNum, columnNum);

            int hexIndex = jsonHexIndex.second.get<int>("");

            BattleHex * hex = hexs.at(hexIndex)->clone();

            battleMap->addHex(location, hex);

            columnNum++;
        }
        rowNum++;
        columnNum = 0;
    }

    for (BattleHex * hex : hexs) {
        delete hex;
    }

    battleMap->initMapNeighbors();

    return battleMap;

}

BattleHex * decodeHex(pt::ptree::value_type * jsonHex, TextureCache * textureCache)
{
    int type = jsonHex->second.get<int>("type", -1);

    switch (type)
    {
    case 0:
        {
            BattleHex * newHex = new BattleHex();

            std::string NorthWestHighlight = jsonHex->second.get<std::string>("HighlightNorthWest");
            newHex->setBorderTexture(textureCache->getTexture(NorthWestHighlight), NorthWest);

            std::string NorthHighlight = jsonHex->second.get<std::string>("NorthHighlight");
            newHex->setBorderTexture(textureCache->getTexture(NorthHighlight), North);

            std::string NorthEastHighlight = jsonHex->second.get<std::string>("NorthEastHighlight");
            newHex->setBorderTexture(textureCache->getTexture(NorthEastHighlight), NorthEast);

            std::string SouthEastHighlight = jsonHex->second.get<std::string>("SouthEastHighlight");
            newHex->setBorderTexture(textureCache->getTexture(SouthEastHighlight), SouthEast);

            std::string SouthHighlight = jsonHex->second.get<std::string>("SouthHighlight");
            newHex->setBorderTexture(textureCache->getTexture(SouthHighlight), South);

            std::string SouthWestHighlight = jsonHex->second.get<std::string>("SouthWestHighlight");
            newHex->setBorderTexture(textureCache->getTexture(SouthWestHighlight), SouthWest);

            int i = 0;
            for (pt::ptree::value_type & pathTexture : jsonHex->second.get_child("PathTextures")) {
                newHex->setPathTexture(*(textureCache->getTexture(pathTexture.second.data())), (Direction)i);
                i++;
            }

            std::string TileTexture = jsonHex->second.get<std::string>("TileTexture");
            newHex->setHexTexture(textureCache->getTexture(TileTexture));
            
            std::string OverlayTexture = jsonHex->second.get<std::string>("OverlayTexture");
            newHex->setHexOverlayTexture(textureCache->getTexture(OverlayTexture));

            std::string SkirtTexture = jsonHex->second.get<std::string>("SkirtTexture");
            newHex->setSkirtTexture(textureCache->getTexture(SkirtTexture));

            int orientation = jsonHex->second.get<int>("orientation");
            int width = jsonHex->second.get<int>("width");
            int height = jsonHex->second.get<int>("height");
            int peakHeight = jsonHex->second.get<int>("peakHeight");
            int level = jsonHex->second.get<int>("level");

            newHex->setDimensions((Orientation)orientation, width, height, peakHeight, level);


            return newHex;
        }
        break;
    default:
        return nullptr;
        break;
    }
}