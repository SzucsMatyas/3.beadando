#include "pushbutton.hpp"

using namespace std;
using namespace genv;


PushButton::PushButton(int x, int y, int sx, int sy, std::string s, std::function<void()> functor)
    : Widget(x,y,sx,sy), _felirat(s), _functor(functor)

{

}

void PushButton::handle(genv::event ev) {
    if(is_selected(ev.pos_x, ev.pos_y) && ev.button==+btn_left){
        focus=1;
    }
    if(focus && ev.button==-btn_left){
        focus=0;
    }
    if((ev.button==btn_left && is_selected(ev.pos_x, ev.pos_y)) || (ev.keycode==key_enter && focus)){
        action();
    }

}

void PushButton::draw(){
    gout << color(0,0,0) << move_to(_X, _Y) << box(_SX, _SY);
    if (focus)
        gout << color(200,200,200);
    else
        gout << color(160,160,160);
    gout << move_to(_X+1, _Y+1) << box(_SX-2, _SY-2);
    gout << color(0,0,0) << move_to(_X+_SX/2-gout.twidth(_felirat)/2, _Y+_SY/2 +4) << text(_felirat);
}

int PushButton::get_val(){
    return -1;
}

void PushButton::action(){
    _functor();
}

void PushButton::t_effects(int XX, int YY)
{
}
