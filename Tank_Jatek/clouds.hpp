#ifndef CLOUDS_HPP_INCLUDED
#define CLOUDS_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"

class Clouds : public Widget {
private:
    int XX, YY;
    double wind;
public:
    Clouds(int x, int y, int sx, int sy, int xx, int yy);
    virtual void draw(genv::event ev) ;
    virtual void set_wind(double w){wind=w;};
};


#endif // CLOUDS_HPP_INCLUDED
