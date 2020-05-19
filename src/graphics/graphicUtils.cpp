#include "graphicUtils.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;


void GraphicUtils::loadTextureFile(std::string file, TextureCache * textureCache)
{
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("assets/" + file);

    pt::ptree tree;
    pt::read_json(fullPath, tree);

    for (pt::ptree::value_type & jsonTexture : tree) {

        std::string label = jsonTexture.second.get<std::string>("label");
        std::string file = jsonTexture.second.get<std::string>("file");

        int x = jsonTexture.second.get<int>("x", -1);
        int y = jsonTexture.second.get<int>("y", -1);

        int width = jsonTexture.second.get<int>("width", -1);
        int height = jsonTexture.second.get<int>("height", -1);

        int type = jsonTexture.second.get<int>("type", 0);

        switch (type)
        {
            case 0:
                {
                    Texture * texture = new Texture(file, x, y, width, height);
                    textureCache->stashTexture(label, texture);
                }
                break;
            case 1:
                {
                    int frameCount = jsonTexture.second.get<int>("frames");
                    float animationSpeed = jsonTexture.second.get<float>("speed");
                    int animationDir = jsonTexture.second.get<int>("direction");
                    
                    AnimatedTexture * animatedTexture = new AnimatedTexture(file, x, y, width, height, frameCount, animationSpeed, (AnimatedTexture::ANIM_DIR) animationDir);
                    textureCache->stashAnimatedTexture(label, animatedTexture);
                }
                break;
            default:
                break;
        }
    }
}
