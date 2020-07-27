#ifndef PATH_HPP
#define PATH_HPP

#include "geometry/gamingVector.hpp"

#include "objects/gameEntity.hpp"

#include "graphics/textures/texture.hpp"

enum PathStatus {
    outOfBounds = 1,
    undefined,
    valid
};

class Path : public GameEntity {
    public:
        Path();
        ~Path();

        virtual double getOutput(double);
        virtual GVector getInterval(double, int) = 0;
        
        PathStatus getStatus();

        virtual void render() = 0;
        virtual void render(Texture *, int) = 0;

        virtual void setStart(GVector) = 0;
        virtual void setEnd(GVector, SPACE = world) = 0;

    protected:
        PathStatus mStatus;
};

#endif