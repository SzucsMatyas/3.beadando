#include "clouds.hpp"
#include "graphics.hpp"

using namespace genv;

Clouds::Clouds(int x, int y, int sx, int sy, int xx, int yy)
    : Widget(x,y,sx,sy)
{
    XX=xx;
    YY=yy;
    focusable = 0;
}

void Clouds::draw()
{
    if(_X+wind<=XX && _X+wind>=0)
        _X+=wind;
    if(_X+wind>XX)
        _X=_X+wind-XX;
    if(_X+wind<0)
        _X=XX-_X+wind;
    if(_X+_SX<=XX)
        gout << move_to(_X, _Y) << color(255,255,255) << box(_SX,_SY);
    if(_X+_SX>XX){
        gout << move_to(_X, _Y) << color(255,255,255) << box(XX-_X,_SY);
        gout << move_to(0, _Y) << color(255,255,255) << box(_X+_SX-XX,_SY);
    }
}
