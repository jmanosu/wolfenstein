#include "inputManager.hpp"

InputManager * InputManager::sInstance = nullptr;

InputManager * InputManager::instance()
{
    if(sInstance == nullptr)
    {
        sInstance = new InputManager();
    }
    return sInstance;
}

void InputManager::release()
{
    delete sInstance;
}

InputManager::InputManager()
{
    mQuit = false;
    mOldMouseX = -1;
    mOldMouseY = -1;
    mCurrentMouseX = 0;
    mCurrentMouseY = 0;
    mDragX = 0;
    mDragY = 0;
}

InputManager::~InputManager()
{
    
}

bool InputManager::keyDown(SDL_EventType code)
{
    return (mCurrentEvent.type == code);
}

void InputManager::update()
{
//    mKeyPressList.erase(mKeyPressList.begin(), mKeyPressList.end());

    while (SDL_PollEvent(&mCurrentEvent)) {
        switch (mCurrentEvent.type) {
            case SDL_QUIT:
                mQuit = true;
                break;
            case SDL_KEYDOWN:
                handleKeyboardPress(mCurrentEvent.key);
                break;
            case SDL_KEYUP:
                handleKeyboardRelease(mCurrentEvent.key);
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleMousePress(mCurrentEvent.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                handleMouseRelease(mCurrentEvent.button.button);
                break;
            case SDL_MOUSEMOTION:
                handleMouseMotion();
                break;
            case SDL_WINDOWEVENT:
                handleWindowEvent(mCurrentEvent.window.event);
                break;
            default:
                break;
        }
    }
}

void InputManager::handleKeyboardPress(SDL_KeyboardEvent event)
{
    bool found = 0;

    for (int i = 0; i < mKeyPressList.size(); i++) {
        if (mKeyPressList.at(i).sym == event.keysym.sym) {
            found = 1;
        }
    }

    if (!found) {
        mKeyPressList.push_back(event.keysym);
    }

    mKeyMod = event.keysym.mod;
/*
    switch(event){
        default:
            break;
    }
*/
}

void InputManager::handleKeyboardRelease(SDL_KeyboardEvent event)
{
    for (int i = 0; i < mKeyPressList.size(); i++) {
        if (mKeyPressList.at(i).sym == event.keysym.sym) {
            mKeyPressList.erase(mKeyPressList.begin() + i);
        }
    }

}

void InputManager::handleMousePress(SDL_Keycode event)
{
    switch (event){
        case SDL_BUTTON_LEFT:
            SDL_GetMouseState(&mOldMouseX, &mOldMouseY);
            break;
        case SDL_BUTTON_RIGHT:
            break;
        default:
            break;
    }
}

void InputManager::handleMouseRelease(SDL_Keycode event)
{
    mOldMouseX = -1;
    mOldMouseY = -1;
}

void InputManager::handleMouseMotion()
{
    SDL_GetMouseState(&mCurrentMouseX, &mCurrentMouseY);
    if (mOldMouseX != -1 && mOldMouseY != -1)
    {
        mDragX = mCurrentMouseX - mOldMouseX;
        mDragY = mCurrentMouseY - mOldMouseY;
        mOldMouseX = mCurrentMouseX;
        mOldMouseY = mCurrentMouseY;
    } else
    {
        mDragX = 0;
        mDragY = 0;
    }
}

void InputManager::handleWindowEvent(SDL_Keycode event)
{
    switch (event){
        case SDL_WINDOWEVENT_LEAVE:
            mOldMouseY = 1;
            mOldMouseX = -1;
            mDragX = 0;
            mDragY = 0;
        default:
            break;
    }
}