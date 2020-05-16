#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

#include "geometry/gamingVector.hpp"

#include "graphics/graphics.hpp"

struct KeyState {
    uint8_t previousState = 3;
    uint8_t state = 3;
};

struct MouseButtonState {
    uint8_t previousState = 3;
    uint8_t state = 3;
    uint8_t clicks;
};

class InputManager{
    private:

        InputManager();
        ~InputManager();

        void handleMouseMotion(SDL_Event &);

        void setMouseButtonState(uint8_t button, uint8_t state);

        void handleMouseUp(SDL_Event &);
        void handleMouseDown(SDL_Event &);

        void setKeyState(SDL_Keycode, uint8_t state);

        void handleKeyUp(SDL_Event &);
        void handleKeyDown(SDL_Event &);

        static InputManager * sInstance;

        int mMouseX, mMouseY;

        bool mQuit;

        std::map<SDL_Keycode, KeyState> mKeyStates;

        std::map<uint8_t, MouseButtonState> mMouseButtonStates;

    public:
        static InputManager * instance();
        static void release();

        bool keyPress(SDL_Keycode);
        bool keyDown(SDL_Keycode);
        bool keyRelease(SDL_Keycode);

        bool mousePress(uint8_t);
        bool mouseDown(uint8_t);
        bool mouseRelease(uint8_t);

        void update();

        int getMouseX();
        int getMouseY();

        bool quit();
        
};

#endif