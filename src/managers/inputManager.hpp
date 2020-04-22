#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

#include "game/utils/gamingVector.hpp"

class InputManager{
    private:

        InputManager();
        ~InputManager();

        static InputManager * sInstance;

        SDL_Event mCurrentEvent;
        SDL_Event mPreviousEvent;

        bool mQuit;

        int mOldMouseX, mOldMouseY;
        int mDragX, mDragY;
        int mCurrentMouseX, mCurrentMouseY;

        std::vector<SDL_Keysym> mKeyPressList;
        int mKeyMod;

    public:
        static InputManager * instance();
        static void release();

        bool keyDown(SDL_EventType);
        void update();

        void handleMousePress(SDL_Keycode);
        void handleMouseRelease(SDL_Keycode);
        void handleKeyboardPress(SDL_KeyboardEvent);
        void handleKeyboardRelease(SDL_KeyboardEvent);
        void handleMouseMotion();
        void handleWindowEvent(SDL_Keycode);

        GVector getCurrentMousePos() { return GVector(mCurrentMouseX, mCurrentMouseY);}
        GVector getMouseDrag() { return GVector(mDragX, mDragY); }

        SDL_Event getCurrentEvent() { return mCurrentEvent; }

        SDL_Keysym getKeyPress(int index) { return mKeyPressList.at(index); }

        int getKeyPressCount() { return mKeyPressList.size(); }

        bool didQuit() { return mQuit; }
};

#endif