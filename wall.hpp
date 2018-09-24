#ifndef wall_hpp
#define wall_hpp

#include <iostream>

struct Color{
  int r;
  int g;
  int b;
};

class Wall{
  public:
    Wall();
    ~Wall();
    void init(Color);
    void init(int, int, int);
    Color get_color();
  private:
    Color wallc;
    bool floor;
};

#endif
