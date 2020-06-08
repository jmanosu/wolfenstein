#ifndef PATHTEXTURE_HPP
#define PATHTEXTURE_HPP

#include "graphics/textures/texture.hpp"

#include "geometry/path.hpp"

class TexturePath {
    public:
        TexturePath();
        ~TexturePath();

        void render();

        void setTexture(const Texture &);

        void setPath(Path *);
        
        void setDX(double);
        void setLowerX(double);
        void setUpperX(double);



    private:
        Path * mPath;

        Texture mTexture;

        double mDX, mLowerX, mUpperX;
};

#endif