#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <SDL2/SDL.h>
#include <iostream>
#include "gamingVector.hpp"

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

        GVector::GVector getCurrentMousePos() { return GVector::GVector(mCurrentMouseX, mCurrentMouseY);}
        GVector::GVector getMouseDrag() { return GVector::GVector(mDragX, mDragY);}

        bool didQuit() { return mQuit; }
};

#endif