#ifndef TEXTURECACHE_HPP
#define TEXTURECACHE_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <tuple>

#include "graphics/textures/texture.hpp"
#include "graphics/textures/animatedTexture.hpp"

class TextureCache {
    public:
        static TextureCache * instance();
        static void release();

        void stashTexture(std::string name, Texture * texture);
        Texture * getTexture(std::string name);
        Texture * generateTexture(std::string name);

        void stashAnimatedTexture(std::string name, AnimatedTexture * texture);
        AnimatedTexture * getAnimatedTexture(std::string name);
        AnimatedTexture * generateAnimatedTexture(std::string name);

    private:
        TextureCache();
        ~TextureCache();

        static TextureCache * sInstance;

        std::map<std::string, Texture *> mTextures;
        std::map<std::string, AnimatedTexture *> mAnimatedTexture;
};

#endif