#ifndef LINE_HPP
#define LINE_HPP

#include "geometry/path.hpp"

class Line : public Path {
    public:
        Line();
        Line(double, double, double, double);
        ~Line();

        double getOutput(double);

        GVector getInterval(double, int);

        void render();
        void render(Texture *, int);

        void setStart(GVector);
        void setEnd(GVector, SPACE = world);

    private:
        GVector mEnd;
};

#endif