#include "textureCache.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>


namespace pt = boost::property_tree;

TextureCache * TextureCache::sInstance = nullptr;

TextureCache * TextureCache::instance()
{
  if (sInstance == nullptr) {
      sInstance = new TextureCache();
  }

  return sInstance;
}

void TextureCache::release()
{
    delete sInstance;
}


TextureCache::TextureCache()
{

}

TextureCache::~TextureCache()
{
  for(auto & texture : mTextures) {
    delete texture.second;
  }
}

void TextureCache::stashTexture(std::string name, Texture * texture)
{
  if (mTextures[name] != nullptr) {
    delete mTextures[name];
  }

  mTextures[name] = texture;
}

Texture * TextureCache::getTexture(std::string name)
{ 
  std::map<std::string, Texture *>::iterator it;

  it = mTextures.find(name);

  if (it != mTextures.end()) {
    return it->second;
  } else {
    return nullptr;
  }
}


void print(boost::property_tree::ptree const& pt)
{
    using boost::property_tree::ptree;
    ptree::const_iterator end = pt.end();
    for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
        std::cout << it->first << ": " << it->second.get_value<std::string>() << std::endl;
        print(it->second);
    }
}

void TextureCache::loadFile(std::string file)
{
  std::string fullPath = SDL_GetBasePath();
  fullPath.append("assets/" + file);

  pt::ptree tree;
  pt::read_json(fullPath, tree);

  for (pt::ptree::value_type & texture : tree) {
    std::string label = texture.second.get<std::string>("label");
    std::string file = texture.second.get<std::string>("file");

    int x = texture.second.get<int>("x", -1);
    int y = texture.second.get<int>("y", -1);

    int width = texture.second.get<int>("width", -1);
    int height = texture.second.get<int>("height", -1);

    if (label != "" && file != "") {
      if (x == -1 || y == -1 || width == -1 || height == -1) {
        stashTexture(label, new Texture(file));
      } else {
        stashTexture(label, new Texture(file, x, y, width, height));
      }
    }
  }
}