#include "animatedTexture.hpp"

AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int width, int height, int frameCount, float animationSpeed, ANIM_DIR animationDir)
    : Texture(filename, x, y, width, height)
{
    mTimer = Timer::instance();
    
    mStartX = x;
    mStartY = y;

    mFrameCount = frameCount;
    mAnimationSpeed = animationSpeed;
    mTimePerFrame = animationSpeed / frameCount;
    mAnimationTimer = 0.0f;

    mAnimationDirection = animationDir;

    mAnimationDone = false;

    mWrapMode = loop;

}

AnimatedTexture::~AnimatedTexture()
{

}

void AnimatedTexture::WrapMode(WRAP_MODE mode)
{
    mWrapMode = mode;
}

void AnimatedTexture::update()
{
    if(!mAnimationDone) {
        mAnimationTimer += mTimer->deltaTime();

        if(mAnimationTimer >= mAnimationSpeed) {
            if (mWrapMode == loop) {
                mAnimationTimer -= mAnimationSpeed;
            } else {
                mAnimationDone = true;
                mAnimationTimer = mAnimationSpeed - mTimePerFrame;
            }
        }
    }

    if(mAnimationDirection == horizontal) {
        mClipRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;
    } else {
        mClipRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
    }

    GVector scaller = this->scale(world);
    GVector pos = this->pos(world);
}

