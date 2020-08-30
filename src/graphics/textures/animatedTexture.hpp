#ifndef ANIMATEDTEXTURE_HPP
#define ANIMATEDTEXTURE_HPP

#include <iostream>

#include "graphics/textures/texture.hpp"

#include "gameplay/timer/timer.hpp"

class AnimatedTexture : public Texture {
    public:
        enum ANIM_DIR {horizontal = 0, vertical =1};
        enum WRAP_MODE {once = 0, loop = 1};

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
        AnimatedTexture();
        AnimatedTexture(const AnimatedTexture &);
        AnimatedTexture(std::string filename, int x, int y, int width, int height, int frameCount, float animationSpeed, ANIM_DIR animationDir);
        ~AnimatedTexture();

        void WrapMode(WRAP_MODE mode);

        void update();
};

namespace AnimatedTextureUtils {
    void copy(const AnimatedTexture * & source, AnimatedTexture * & destination);
};


#endif