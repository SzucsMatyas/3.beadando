#ifndef TANK_HPP_INCLUDED
#define TANK_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include "master.hpp"
#include <vector>

class Tank : public Widget {
private:
    int r, g, b;
    double main_hp, top_hp, front_hp, back_hp, shp_part, mhp_part, deg;
    char oldal;
public:
    Tank(int x, int y, int sx, int sy, double mhp, double shp, int _r, int _g, int _b, char _oldal);
    virtual void draw() ;
    virtual void handle(genv::event ev);
    virtual void t_effects(Master mester);
    virtual int get_val();
    virtual bool hit_det(double msx, double msy, int XX, int YY);
//    virtual int get_X(){return _X;}
//    virtual int get_Y(){return _Y;}
//    virtual int get_SX(){return _SX;}
//    virtual int get_SY(){return _SY;}
//    virtual double get_top(){return top_hp;}
//    virtual double get_front(){return front_hp;}
//    virtual double get_back(){return back_hp;}
};

#endif // TANK_HPP_INCLUDED
