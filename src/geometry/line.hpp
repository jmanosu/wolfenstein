#ifndef LINE_HPP
#define LINE_HPP

#include "geometry/gamingVector.hpp"

#include "geometry/path.hpp"

class Line : public Path {
    public:
        Line();
        Line(double, double, double, double);
        ~Line();

        double getOutput(double);

        GVector getInterval(double, int);
    private:
        GVector mBegin;
        GVector mEnd;
};

#endif