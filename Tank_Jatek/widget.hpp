#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

#include "graphics.hpp"
#include <vector>

class Widget {
protected:
    int _X, _Y, _SX, _SY;
    bool focus, focusable;
public:
    Widget(int x, int y, int sx, int sy);
    virtual bool is_selected(int mx, int my);
    virtual bool custom_is_selected(int mx, int my, int XX, int YY, int SXX, int SYY);
    virtual void set_focus(bool temp);
    virtual bool get_focus();
    virtual bool get_focusable();
    virtual void handle(genv::event ev) = 0;
//    virtual void t_effects(int XX, int YY, ) = 0;
    virtual void draw() = 0;
    virtual int get_val() = 0;
};

                                                                                                                                                                                                                                                                  //szeretnek pontlevonast kerni a beadandomra mert feltoltottem egy oktatasi segedletet sajat munka helyett :)

#endif // WIDGET_HPP_INCLUDED
