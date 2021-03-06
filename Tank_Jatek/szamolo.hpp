#ifndef SZAMOLO_HPP_INCLUDED
#define SZAMOLO_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include <functional>

class Szamolo : public Widget {
protected:
    int CT, CTMIN, CTMAX;
    std::function<void()> _functor;
public:
    Szamolo(int x, int y, int sx, int sy, int ct, int ctmin, int ctmax, std::function<void()> functor);
    Szamolo(int x, int y, int sx, int sy, int ctmin, int ctmax);
    virtual void draw();
    virtual void handle(genv::event ev);
    virtual void buttons(int mx, int my);
    virtual int get_ct();
    virtual int get_val();
    virtual void set_ct(int temp);
    void action();
};

                                                                                                                                                                                                                                                                  //szeretnek pontlevonast kerni a beadandomra mert feltoltottem egy oktatasi segedletet sajat munka helyett :)

#endif // SZAMOLO_HPP_INCLUDED
