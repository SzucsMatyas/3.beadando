#include "szamolo.hpp"
#include "graphics.hpp"
#include <sstream>

using namespace genv;

Szamolo::Szamolo(int x, int y, int sx, int sy, int ct, int ctmin, int ctmax, std::function<void()> functor) : Widget(x,y,sx,sy), _functor(functor), CT(ct), CTMIN(ctmin), CTMAX(ctmax)
{
}

Szamolo::Szamolo(int x, int y, int sx, int sy, int ctmin, int ctmax) : Widget(x,y,sx,sy), CT(ctmin), CTMIN(ctmin), CTMAX(ctmax)
{
}


void Szamolo::handle(event ev)
{
    if(focusable)
    {
        if (is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left) {
            focus = 1;
            buttons(ev.pos_x, ev.pos_y);
        }
        if (!is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left){
            focus= 0;
        }

        if (focus && ev.keycode == +key_pgup && CT+10 > CTMAX){
            CT = CTMAX;
        }
        if (focus && ev.keycode == +key_pgup && CT+10 <= CTMAX){
            CT+=10;
        }
        if (focus && ev.keycode == +key_up && CT+1 <= CTMAX){
            CT++;
        }
        if (focus && ev.button == btn_wheelup && CT+1 <= CTMAX){
            CT++;
        }

        if (focus && ev.keycode == +key_pgdn && CT-10 < CTMIN){
            CT = CTMIN;
        }
        if (focus && ev.keycode == +key_pgdn && CT-10 >= CTMIN){
            CT-=10;
        }
        if (focus && ev.keycode == +key_down && CT-1 >= CTMIN){
            CT--;
        }
        if (focus && ev.button == btn_wheeldown && CT-1 >= CTMIN){
            CT--;
        }
        action();
    }
}

void Szamolo::draw()
{
    std::stringstream SS;
    SS << CT;
    if (focus && focusable){
        gout << move_to(_X, _Y) << color(0,0,0) << box(_SX, _SY);
        gout << move_to(_X+1, _Y+1) << color(153,255,153) << box(_SX-_SY/2, _SY-2);
        gout << move_to(_X+4, _Y+(_SY/2)+4) << color(0,0,0) << text(SS.str());

        gout << move_to(_X+_SX-_SY/2 +2, _Y+1) << color(153,255,153) << box(_SY/2 -3, _SY/2 -1);

        gout << move_to(_X+_SX-_SY/2 +2, _Y+_SY/2 +1) << color(153,255,153) << box(_SY/2 -3, _SY/2 -2);

        gout << move_to(_X+_SX-(_SY/2)+(_SY/4)-3, _Y+(_SY/4)+5) << color(0,0,0) << text("+");
        gout << move_to(_X+_SX-(_SY/2)+(_SY/4)-3, _Y+(_SY/4)*3+4) << color(0,0,0) << text("-");
        }
    if (!focus && focusable && !hovered){
        gout << move_to(_X, _Y) << color(0,0,0) << box(_SX, _SY);
        gout << move_to(_X+1, _Y+1) << color(160,160,160) << box(_SX-_SY/2, _SY-2);
        gout << move_to(_X+4, _Y+(_SY/2)+4) << color(0,0,0) << text(SS.str());

        gout << move_to(_X+_SX-_SY/2 +2, _Y+1) << color(160,160,160) << box(_SY/2 -3, _SY/2 -1);

        gout << move_to(_X+_SX-_SY/2 +2, _Y+_SY/2 +1) << color(160,160,160) << box(_SY/2 -3, _SY/2 -2);

        gout << move_to(_X+_SX-(_SY/2)+(_SY/4)-3, _Y+(_SY/4)+5) << color(0,0,0) << text("+");
        gout << move_to(_X+_SX-(_SY/2)+(_SY/4)-3, _Y+(_SY/4)*3+4) << color(0,0,0) << text("-");
    }
    if (!focus && focusable && hovered){
        gout << move_to(_X, _Y) << color(0,0,0) << box(_SX, _SY);
        gout << move_to(_X+1, _Y+1) << color(200,200,200) << box(_SX-_SY/2, _SY-2);
        gout << move_to(_X+4, _Y+(_SY/2)+4) << color(0,0,0) << text(SS.str());

        gout << move_to(_X+_SX-_SY/2 +2, _Y+1) << color(200,200,200) << box(_SY/2 -3, _SY/2 -1);

        gout << move_to(_X+_SX-_SY/2 +2, _Y+_SY/2 +1) << color(200,200,200) << box(_SY/2 -3, _SY/2 -2);

        gout << move_to(_X+_SX-(_SY/2)+(_SY/4)-3, _Y+(_SY/4)+5) << color(0,0,0) << text("+");
        gout << move_to(_X+_SX-(_SY/2)+(_SY/4)-3, _Y+(_SY/4)*3+4) << color(0,0,0) << text("-");
    }
    if (!focusable){
        gout << move_to(_X, _Y) << color(0,0,0) << box(_SX, _SY);
        gout << move_to(_X+1, _Y+1) << color(120,120,120) << box(_SX-_SY/2, _SY-2);
        gout << move_to(_X+4, _Y+(_SY/2)+4) << color(0,0,0) << text(SS.str());

        gout << move_to(_X+_SX-_SY/2 +2, _Y+1) << color(120,120,120) << box(_SY/2 -3, _SY/2 -1);

        gout << move_to(_X+_SX-_SY/2 +2, _Y+_SY/2 +1) << color(120,120,120) << box(_SY/2 -3, _SY/2 -2);

        gout << move_to(_X+_SX-(_SY/2)+(_SY/4)-3, _Y+(_SY/4)+5) << color(0,0,0) << text("+");
        gout << move_to(_X+_SX-(_SY/2)+(_SY/4)-3, _Y+(_SY/4)*3+4) << color(0,0,0) << text("-");
    }
}

void Szamolo::buttons(int mx, int my)
{
    if(mx>=_X+_SX-_SY/2 +2 && mx<=_X+_SX-1 && my>=_Y+1 && my<=_Y+_SY/2 -1 && CT+1 <= CTMAX)
        CT++;
    if(mx>=_X+_SX-_SY/2 +2 && mx<=_X+_SX-1 && my>=_Y+_SY/2 && my<=_Y+_SY-1 && CT-1 >= CTMIN)
        CT--;
}

int Szamolo::get_ct()
{
    return CT;
}

int Szamolo::get_val()
{
    return CT;
}

void Szamolo::set_ct(int temp)
{
    CT=temp;
}

void Szamolo::action(){
    _functor();
}
