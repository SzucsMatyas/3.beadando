#ifndef PUSHBUTTON_HPP_INCLUDED
#define PUSHBUTTON_HPP_INCLUDED

#include "widget.hpp"
#include "window.hpp"
#include <functional>

class PushButton : public Widget {
    std::string _felirat;
    std::function<void()> _functor;
public:
    PushButton(int x, int y, int sx, int sy, std::string s, std::function<void()> functor);
    virtual void draw();
    virtual void handle(genv::event ev);
    virtual void t_effects(int XX, int YY);
    virtual int get_val();
    void action();
};
#endif // PUSHBUTTON_HPP_INCLUDED
