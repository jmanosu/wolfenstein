#include "screenManager.hpp"

ScreenManager * ScreenManager::sInstance = nullptr;

ScreenManager * ScreenManager::instance()
{
    if(sInstance == nullptr) {
        sInstance = new ScreenManager();
    }
    return sInstance;
}

void ScreenManager::release()
{
    if(sInstance != nullptr) {
        delete sInstance;
    }
}


ScreenManager::ScreenManager()
{
    mActiveScreen = nullptr;
}

ScreenManager::~ScreenManager()
{
    for(auto screen: mScreens)
    {
        if(screen.second != nullptr)
        {
            delete screen.second;
        }
    }
}

void ScreenManager::addScreen(std::string screenName, Screen * screen)
{
    if(mScreens[screenName] == nullptr) {
        mScreens[screenName] = screen;
    }
}

void ScreenManager::setCurrentScreen(std::string screenName)
{
    std::map<std::string, Screen *>::iterator it = mScreens.find(screenName);
    if(it->second != nullptr) {
        mActiveScreen = mScreens[screenName];   
    }
}

void ScreenManager::render()
{
    if(mActiveScreen != nullptr) {
        mActiveScreen->render();
    }
}

void ScreenManager::update()
{
    if(mActiveScreen != nullptr) {
        mActiveScreen->update();
    }
}
