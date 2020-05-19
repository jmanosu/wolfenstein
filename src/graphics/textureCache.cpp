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

  for(auto & texture: mAnimatedTexture) {
    delete texture.second;
  }
}

void TextureCache::stashTexture(std::string name, Texture * texture)
{
  std::map<std::string, Texture *>::iterator it = mTextures.find(name);

  if (it != mTextures.end()) {
    delete it->second;
  }

  mTextures[name] = texture;
}

Texture * TextureCache::getTexture(std::string name)
{ 
  std::map<std::string, Texture *>::iterator it = mTextures.find(name);

  if (it != mTextures.end()) {
    return it->second;
  } else {
    return nullptr;
  }
}

void TextureCache::stashAnimatedTexture(std::string name, AnimatedTexture * texture)
{
  std::map<std::string, AnimatedTexture *>::iterator it = mAnimatedTexture.find(name);

  if (it != mAnimatedTexture.end()) {
    delete it->second;
  }

  mAnimatedTexture[name] = texture;
}

AnimatedTexture * TextureCache::getAnimatedTexture(std::string name)
{
  std::map<std::string, AnimatedTexture *>::iterator it = mAnimatedTexture.find(name);

  if (it != mAnimatedTexture.end()) {
    return it->second;
  } else {
    return nullptr;
  }

}