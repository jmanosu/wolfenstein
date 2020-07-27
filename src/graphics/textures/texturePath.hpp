#ifndef PATHTEXTURE_HPP
#define PATHTEXTURE_HPP

#include "graphics/textures/texture.hpp"

#include "geometry/path.hpp"

class TexturePath : public GameEntity {
    public:
        TexturePath();
        ~TexturePath();

        void render();

        void setTexture(const Texture &);

        void setPath(Path *);

        void setStart(GVector);
        void setEnd(GVector);
    private:
        Path * mPath;

        Texture mTexture;
};

#endif