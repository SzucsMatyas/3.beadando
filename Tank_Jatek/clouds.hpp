#ifndef CLOUDS_HPP_INCLUDED
#define CLOUDS_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"

class Clouds : public Widget {
private:
    int wind;
public:
    Clouds(int x, int y, int sx, int sy);
    virtual void draw() ;
    virtual void handle(genv::event ev);
    virtual void t_effects(genv::event ev);
    virtual int get_val();
};


#endif // CLOUDS_HPP_INCLUDED
