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

    for(auto text: mTextTextures)
    {
        if(text.second != nullptr)
        {
            SDL_DestroyTexture(text.second);
        }
    }
    mTextTextures.clear();

    for(auto font: mFonts)
    {
        if(font.second != nullptr)
        {
            TTF_CloseFont(font.second);
        }
    }
    mFonts.clear();
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

SDL_Texture * assetManager::getTextTexture(std::string text, std::string fileName, int size, SDL_Color color) {
    TTF_Font * font = getFont(fileName, size);
    std::string key = text + fileName + (char)(size);

    if(mTextTextures[key] == nullptr){
        mTextTextures[key] = Graphics::instance()->createTextTexture(font, text, color);
        if(mTextTextures[key] == nullptr){
            std::cout << "ERROR loading text texture" << std::endl;
        }
    }
    return mTextTextures[key];
}

TTF_Font * assetManager::getFont(std::string fileName, int size) {
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("assets/" + fileName);
    std::string key = fullPath + (char)(size);

    if(mFonts[key] == nullptr){
        mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);
        if(mFonts[key] == nullptr){
            std::cout << "ERROR loading font " << fileName << " error description " << TTF_GetError() << std::endl;
        }
    }
    return mFonts[key];
}