#include "assetManager.hpp"

assetManager * assetManager::sInstance = nullptr;

assetManager * assetManager::instance()
{
    if(sInstance == nullptr){
        sInstance = new assetManager();
    }
    return sInstance;
}

void assetManager::release()
{
    delete sInstance;
    sInstance = nullptr;
}

assetManager::assetManager(){}

assetManager::~assetManager()
{
    for(auto tex: mTextures)
    {
        if(tex.second != nullptr)
        {
            SDL_DestroyTexture(tex.second);
        }
    }
    mTextures.clear();
}

SDL_Texture * assetManager::getTexture(std::string fileName){
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("assets/" + fileName);
    
    if(mTextures[fullPath] == nullptr){
        mTextures[fullPath] = Graphics::instance()->loadTexture(fullPath);
        if(mTextures[fullPath] == nullptr){
            std::cout << "ERROR loading texture" << std::endl;
        }
    }
    return mTextures[fullPath];
}