#ifndef MAPDRAW_HPP_INCLUDED
#define MAPDRAW_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"

class MapDraw : public Widget {
public:
    MapDraw(int x, int y, int sx, int sy);
    virtual void draw() ;
    virtual void handle(genv::event ev);
    virtual void t_effects(int XX, int YY, int x2, int y2, int sx2, int sy2, double top2, double front2, double back2);
//    virtual void t_effects(genv::event ev);
    virtual int get_val();
    virtual int get_X(){return _X;}
    virtual int get_Y(){return _Y;}
    virtual int get_SX(){return _SX;}
    virtual int get_SY(){return _SY;}
    virtual double get_top(){return 0;}
    virtual double get_front(){return 0;}
    virtual double get_back(){return 0;}
};


#endif // MAPDRAW_HPP_INCLUDED
