#ifndef TEXTURELOADER
#define TEXTURELOADER

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <tuple>
#include "texture.hpp"

class TextureCache {
    public:
        static TextureCache * instance();
        static void release();

        void stashTexture(std::string name, Texture * texture);
        Texture * getTexture(std::string name);

    private:
        TextureCache();
        ~TextureCache();

        static TextureCache * sInstance;

        std::map<std::string, Texture *> mTextures;
};

#endif