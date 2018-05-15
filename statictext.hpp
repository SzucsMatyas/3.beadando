#ifndef STATICTEXT_HPP_INCLUDED
#define STATICTEXT_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"

class StaticText : public Widget {
private:
    std::string txt;
public:
    StaticText(int x, int y, int sx, int sy, std::string _txt);
    virtual void draw() ;
    virtual void handle(genv::event ev);
    virtual void set_text(std::string s);
    virtual int get_val();
};


#endif // STATICTEXT_HPP_INCLUDED
