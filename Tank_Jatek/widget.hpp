#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

#include "graphics.hpp"
#include <vector>

class Widget {
protected:
    double _X, _Y;
    int _SX, _SY;
    bool focus, focusable;
public:
    Widget(double x, double y, int sx, int sy);
    Widget();
    virtual bool is_selected(int mx, int my);
    virtual bool custom_is_selected(int mx, int my, int XX, int YY, int SXX, int SYY);
    virtual void set_focus(bool temp);
    virtual void particle_effect(double bx, double by, double vxb, double vyb, int num, int XX, int YY,std::vector<Widget*> widgets, int R, int G, int B);
    virtual bool get_focus();
    virtual bool get_focusable();
    virtual void handle(genv::event ev);
    virtual void draw(int r, int g, int b);
    virtual void draw(genv::event ev);
    virtual void draw();
    virtual int get_val();
    virtual void bullet_draw(double bx, double by);
};
class Particle : public Widget {
protected:
    double vx,vy;
    int r,g,b;
public:
    Particle(double x, double y, double sx, double sy): Widget(x,y,sx,sy){};
    virtual void set_vx(double Vx) {vx=Vx;};
    virtual void set_vy(double Vy) {vy=Vy;};
    virtual void set_r(int R) {r=R;};
    virtual void set_g(int G) {g=G;};
    virtual void set_b(int B) {b=B;};
    virtual double get_vx() {return vx;};
    virtual double get_vy() {return vy;};
    virtual int get_r() {return r;};
    virtual int get_g() {return g;};
    virtual int get_b() {return b;};
};
#endif // WIDGET_HPP_INCLUDED

