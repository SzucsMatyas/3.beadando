#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include <string>
#include <functional>

class TextBox : public Widget {
private:
    std::string txt;
    std::function<void()> _functor;
    bool _checked, _firstchecked;
public:
    TextBox(int x, int y, int sx, int sy, std::string txt, std::function<void()> _functor);
    virtual void draw() ;
    virtual void handle(genv::event ev);
    virtual void t_effects(genv::event ev);
    virtual void set_text(std::string temp);
    virtual std::string get_text();
    virtual void add_text(char temp);
    virtual void del_text();
    virtual int get_val();
    void set_focus(bool temp);
    void action();
};


#endif // TEXTBOX_HPP_INCLUDED

