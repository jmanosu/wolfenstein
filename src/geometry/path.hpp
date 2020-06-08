#ifndef PATH_HPP
#define PATH_HPP


enum PathStatus {
    outOfBounds = 1,
    undefined,
    valid
};

class Path {
    public:
        Path();
        ~Path();

        virtual double getOutput(double);
        
        PathStatus getStatus();

        void setLowerBound(double);
        void setUppderBound(double);

        double getLowerBound();
        double getUpperBound();

    protected:
        double mLowerBound, mUpperBound;

        PathStatus mStatus;
};

#endif