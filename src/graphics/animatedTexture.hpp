#ifndef ANIMATEDTEXTURE
#define ANIMATEDTEXTURE

#include <iostream>
#include "graphics/texture.hpp"
#include "misc/timer.hpp"

class AnimatedTexture : public Texture {
    public:
        enum WRAP_MODE {once = 0, loop = 1};
        enum ANIM_DIR {horizontal = 0, vertical =1};

    private:
        Timer * mTimer;

        int mStartX;
        int mStartY;

        float mAnimationTimer;
        float mAnimationSpeed;
        float mTimePerFrame;

        int mFrameCount;

        WRAP_MODE mWrapMode;
        ANIM_DIR mAnimationDirection;

        bool mAnimationDone;

    public:

        AnimatedTexture(std::string filename, int x, int y, int width, int height, int frameCount, float animationSpeed, ANIM_DIR animationDir);
        ~AnimatedTexture();

        void WrapMode(WRAP_MODE mode);

        void update();
};

#endif