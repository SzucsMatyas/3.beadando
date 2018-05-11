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
    virtual void draw(genv::event ev) ;
    virtual void handle(genv::event ev);
    virtual int get_val();
    virtual bool hit_det(double msx, double msy, int XX, int YY);
    virtual void set_fronthp(double temp);
    virtual void set_backhp(double temp);
    virtual void set_tophp(double temp);
    virtual void set_mainhp(double temp);
};

#endif // TANK_HPP_INCLUDED
