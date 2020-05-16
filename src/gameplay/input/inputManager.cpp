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
    mMouseX = -1;
    mMouseY = -1;
}

InputManager::~InputManager()
{
    
}

void InputManager::update()
{

    for (auto keyState : mKeyStates) {
        mKeyStates[keyState.first].previousState = mKeyStates[keyState.first].state;
        if (mKeyStates[keyState.first].previousState != 1) {
            mKeyStates[keyState.first].state = 0;
        } else {
            mKeyStates[keyState.first].state = 1;
        }
    }

    for (auto mouseButtonState : mMouseButtonStates) {
        mMouseButtonStates[mouseButtonState.first].previousState = mMouseButtonStates[mouseButtonState.first].state; 
        if (mMouseButtonStates[mouseButtonState.first].previousState != 1) {
            mMouseButtonStates[mouseButtonState.first].state = 0;
        } else {
            mMouseButtonStates[mouseButtonState.first].state = 1;
        }
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            mQuit = true;
            break;
        case SDL_MOUSEMOTION:
            handleMouseMotion(event);
            break;
        case SDL_MOUSEBUTTONUP:
            handleMouseUp(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            handleMouseDown(event);
            break;
        case SDL_KEYDOWN:
            handleKeyDown(event);
            break;
        case SDL_KEYUP:
            handleKeyUp(event);
            break;
        default:
            break;
        }
    }

    for (auto keyState : mKeyStates) {
        if (keyRelease(keyState.first)) {
            std::cout << "KEY: " << SDL_GetKeyName(keyState.first) << " is released" << std::endl;
        }
        if (keyPress(keyState.first)) {
            std::cout << "KEY: " << SDL_GetKeyName(keyState.first) << " is pressed" << std::endl;
        }
    }

    for (auto mouseButtonState : mMouseButtonStates) {
        if (mouseRelease(mouseButtonState.first)) {
            std::cout << "MOUSE BUTTON: " << int(mouseButtonState.first) << " is released" << std::endl;
        }
        if (mousePress(mouseButtonState.first)) {
            std::cout << "MOUSE BUTTON: " << int(mouseButtonState.first) << " is pressed" << std::endl;
        }
    }

}

void InputManager::handleMouseMotion(SDL_Event & event)
{
    mMouseX = event.motion.x;
    mMouseY = event.motion.y;
}

void InputManager::setMouseButtonState(uint8_t button, uint8_t state)
{
    MouseButtonState newMouseButtonState;

    newMouseButtonState.previousState = SDL_RELEASED;
    newMouseButtonState.state = state;

    std::map<uint8_t, MouseButtonState>::iterator it = mMouseButtonStates.find(button);

    if (it != mMouseButtonStates.end()) {
        newMouseButtonState.previousState = it->second.state;
    }

    mMouseButtonStates[button] = newMouseButtonState;
}

void InputManager::handleMouseUp(SDL_Event & event)
{
    setMouseButtonState(event.button.button, event.button.state);;
}

void InputManager::handleMouseDown(SDL_Event & event)
{
    setMouseButtonState(event.button.button, event.button.state);
}

void InputManager::setKeyState(SDL_Keycode keycode, uint8_t state)
{
    KeyState newKeyState;

    newKeyState.previousState = SDL_RELEASED;
    newKeyState.state = state;

    std::map<SDL_Keycode, KeyState>::iterator it = mKeyStates.find(keycode);

    if (it != mKeyStates.end()) {
        newKeyState.previousState = it->second.state;
    }

    mKeyStates[keycode] = newKeyState;
}

void InputManager::handleKeyUp(SDL_Event & event)
{
    setKeyState(event.key.keysym.sym, event.key.state);
}

void InputManager::handleKeyDown(SDL_Event & event)
{
    setKeyState(event.key.keysym.sym, event.key.state);
}

bool InputManager::keyPress(SDL_Keycode code)
{
    return (mKeyStates[code].previousState == 0) && (mKeyStates[code].state == 1);
}

bool InputManager::keyDown(SDL_Keycode code)
{
    return (mKeyStates[code].state == 1);
}

bool InputManager::keyRelease(SDL_Keycode code)
{
    return (mKeyStates[code].previousState == 1) && (mKeyStates[code].state == 0);
}

bool InputManager::mousePress(uint8_t button)
{
    return (mMouseButtonStates[button].previousState == 0) && (mMouseButtonStates[button].state == 1);
}

bool InputManager::mouseDown(uint8_t button)
{
    return (mMouseButtonStates[button].state == 1);
}

bool InputManager::mouseRelease(uint8_t button)
{
    return (mMouseButtonStates[button].previousState == 1) && (mMouseButtonStates[button].state == 0);
}

int InputManager::getMouseX()
{
    return mMouseX;
}

int InputManager::getMouseY()
{
    return mMouseY;
}

bool InputManager::quit()
{
    return mQuit;
}