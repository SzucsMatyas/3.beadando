#include "statictext.hpp"
#include "graphics.hpp"

using namespace genv;

StaticText::StaticText(int x, int y, int sx, int sy, std::string _txt)
    : Widget(x,y,sx,sy)
{
    txt=_txt;
    focusable = 0;
}

void StaticText::handle(event ev)
{
}

void StaticText::draw()
{
    gout << move_to(_X, _Y) << color(0,0,0) << box(_SX,_SY);
    gout << move_to(_X+1, _Y+1) << color(120,120,120) << box(_SX-2,_SY-2);
    gout << color(0,0,0) << move_to(_X+_SX/2-gout.twidth(txt)/2, _Y+_SY/2 +4) << text(txt);
}

int StaticText::get_val()
{
    return -1;
}

void StaticText::set_text(std::string s)
{
    txt = s;
}
