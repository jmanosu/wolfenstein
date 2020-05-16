#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include "objects/gameEntity.hpp"

class BoundingBox : public GameEntity {
    public:
        BoundingBox();
        ~BoundingBox();

        int getWidth();
        void setWidth(int);

        int getHeight();
        void setHeight(int);

        bool collision(int, int);

    private:
        int mWidth, mHeight;

};

#endif