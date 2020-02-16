#include "textureCache.hpp"

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