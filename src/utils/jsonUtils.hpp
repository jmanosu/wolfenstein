#ifndef JSONUTILS_HPP
#define JSONUTILS_HPP

#include "objects/map/battleMap.hpp"

#include "objects/map/hexs/battleHex.hpp"

#include "graphics/textureCache.hpp"

namespace JsonUtils {

    BattleMap * loadBattleMap(std::string, TextureCache *);
    
}

#endif