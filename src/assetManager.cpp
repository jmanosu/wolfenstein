#include "assetManager.hpp"

assetManager * assetManager::sInstance = nullptr;

assetManager * assetManager::instance()
{
    if(sInstance != nullptr){
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

void assetManager::loadTexture(std::string fileName){
    //IMG_LoadTexture(renderer, fileName);
}

SDL_Texture * assetManager::getTexture(std::string fileName){
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("/assets/" + fileName);
    if(mTextures.at(fullPath) == nullptr){
        //create static loader functions
        mTextures[fullPath] = nullptr;
    }
}