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
    mPreviousEvent = mCurrentEvent;
    SDL_PollEvent(&mCurrentEvent);
    switch (mCurrentEvent.type) {
        case SDL_QUIT:
            mQuit = true;
            break;
        case SDL_KEYDOWN:
            handleKeyboardPress(mCurrentEvent.key.keysym.sym);
            break;
        case SDL_KEYUP:
            handleKeyboardRelease(mCurrentEvent.button.button);
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
        default:
            break;
    }
}

void InputManager::handleKeyboardPress(SDL_Keycode event)
{
    switch(event){
        default:
            break;
    }
}

void InputManager::handleKeyboardRelease(SDL_Keycode event)
{

}

void InputManager::handleMousePress(SDL_Keycode event)
{
    switch (event){
        case SDL_BUTTON_LEFT:
            std::cout << "in handleMousePress" << std::endl;
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
    //std::cout << "in handleReleasePress" << std::endl;
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
    } else
    {
        mDragX = 0;
        mDragY = 0;
    }
    std::cout << "dragX: " << mDragX << " dragY: " << mDragY << std::endl; 
    std::cout << "mOldMouseX: " << mOldMouseX << " mOldMouseY: " << mOldMouseY << std::endl;   
}