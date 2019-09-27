#ifndef timer_hpp
#define timer_hpp

#include <iostream>
#include <SDL2/SDL.h>

class Timer {
    public:

        static Timer * instance();
        void release();

        void reset();
        float deltaTime();

        void update();

        void timeScale(float t);
        float timeScale();
    
    private:
        Timer();
        ~Timer();

    private:
    
        static Timer * sInstance;

        unsigned int mStartTick;
        unsigned int mElapsedTick;
        float mDeltaTime;
        float mTimeScale;
};


#endif