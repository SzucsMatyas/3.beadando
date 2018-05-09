#include "clouds.hpp"
#include "graphics.hpp"

using namespace genv;

Clouds::Clouds(int x, int y, int sx, int sy)
    : Widget(x,y,sx,sy)
{
    focusable = 0;
}

void Clouds::handle(event ev)
{
}

void Clouds::draw()
{
    gout << move_to(_X, _Y) << color(150,150,150) << box(_SX,_SY);
//    gout << move_to(_X+1, _Y+1) << color(120,120,120) << box(_SX-2,_SY-2);
}

int Clouds::get_val()
{
    return wind;
}

void Clouds::t_effects(event ev)
{
}
