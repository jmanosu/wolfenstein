#include "timer.hpp"

Timer * Timer::sInstance = nullptr;

Timer * Timer::instance()
{
    if(sInstance == nullptr)
    {
        sInstance = new Timer();
    }

    return sInstance;
}

void Timer::release()
{
    delete sInstance;
}

Timer::Timer()
{
    reset();
    mTimeScale = 1.0f;
}

Timer::~Timer()
{

}

void Timer::reset()
{
    mStartTick = SDL_GetTicks();
    mElapsedTick = 0;
    mDeltaTime = 0.0f;
}

float Timer::deltaTime()
{
    return mDeltaTime;
}

void Timer::update()
{
    mElapsedTick = SDL_GetTicks() - mStartTick;
    mDeltaTime = mElapsedTick * 0.001f;
}

void Timer::timeScale(float t)
{
    mTimeScale = t;
}

float Timer::timeScale()
{
    return mTimeScale;
}