#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <SDL2/SDL.h>
#include <iostream>
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

    public:
        static InputManager * instance();
        static void release();

        bool keyDown(SDL_EventType);
        void update();

        void handleMousePress(SDL_Keycode);
        void handleMouseRelease(SDL_Keycode);
        void handleKeyboardPress(SDL_Keycode);
        void handleKeyboardRelease(SDL_Keycode);
        void handleMouseMotion();
        void handleWindowEvent(SDL_Keycode);

        GVector getCurrentMousePos() { return GVector(mCurrentMouseX, mCurrentMouseY);}
        GVector getMouseDrag() { return GVector(mDragX, mDragY); }

        SDL_Event getCurrentEvent() { return mCurrentEvent; }

        bool didQuit() { return mQuit; }
};

#endif