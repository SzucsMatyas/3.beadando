#include "mapdraw.hpp"
#include "graphics.hpp"

using namespace genv;

MapDraw::MapDraw(int x, int y, int sx, int sy)
    : Widget(x,y,sx,sy)
{
    focusable = 0;
}

void MapDraw::handle(event ev)
{
}

void MapDraw::draw()
{
    gout << move_to(_X, _Y) << color(0,0,0) << box(_SX,_SY);
}

int MapDraw::get_val()
{
    return -1;
}

void MapDraw::t_effects(int XX, int YY, int x2, int y2, int sx2, int sy2, double top2, double front2, double back2)
{
}
