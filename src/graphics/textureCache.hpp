#ifndef TEXTURECACHE_HPP
#define TEXTURECACHE_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <tuple>

#include "graphics/textures/texture.hpp"

class TextureCache {
    public:
        static TextureCache * instance();
        static void release();

        void stashTexture(std::string name, Texture * texture);
        Texture * getTexture(std::string name);

        void loadFile(std::string file);

    private:
        TextureCache();
        ~TextureCache();

        static TextureCache * sInstance;

        std::map<std::string, Texture *> mTextures;
};

#endif