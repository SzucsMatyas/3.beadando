#include "lista.hpp"
#include "graphics.hpp"

using namespace genv;

Lista::Lista(int x, int y, int sx, int sy, int ls, std::vector<std::string> lista) : Widget(x,y,sx,sy)
{
    selected = 0;
    act = 0;
    is_open = 0;
    orig_LS = ls;
    LISTA=lista;
    if(LISTA.size()>ls){
        rolling = 1;
        LS = ls;
    }else{
        rolling = 0;
        LS = LISTA.size();
    }
    if(LISTA.size()==0){
        LISTA.push_back("empty list");
        focusable=0;
    }
    while(y+sy+LS*20 > 400)
        LS--; rolling = 1;

}

void Lista::handle(event ev)
{
    if(is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left && focusable) {
        focus = 1;
        gout << move_to(_X, _Y+_SY) << color(255,255,255) << box(_SX, LS*20);
        button(ev.pos_x, ev.pos_y);
    }
    if(!is_selected(ev.pos_x, ev.pos_y) && !is_open && ev.button==btn_left && focusable){
        focus = 0;
        gout << move_to(_X, _Y+_SY) << color(255,255,255) << box(_SX, LS*20);
    }
    if(!custom_is_selected(ev.pos_x, ev.pos_y, _X, _Y, _SX, _SY+20*LS) && is_open && ev.button==btn_left && focusable){
        focus = 0;
        gout << move_to(_X, _Y+_SY) << color(255,255,255) << box(_SX, LS*20);
        is_open = 0;
    }
    if(focus && ev.keycode == key_enter && focusable) {
        is_open = !is_open;
        gout << move_to(_X, _Y+_SY) << color(255,255,255) << box(_SX, LS*20);
    }
    if(focus && is_open && ev.keycode == key_down && selected+1 < LISTA.size() && focusable) {
        selected += 1;
        if(selected >= act+LS){
            act = selected-LS+1;
        }
    }
    if(focus && is_open && ev.keycode == key_up && selected-1 >= 0 && focusable) {
        selected -= 1;
        if(selected <= act){
            act = selected;
        }
    }
    if(focus && is_open && rolling && ev.button == btn_wheeldown && act+LS < LISTA.size() && focusable){
        act++;
    }
    if(focus && is_open && rolling && ev.button == btn_wheelup && act > 0 && focusable){
        act--;
    }
    if(focus && is_open && ev.button == btn_left && focusable){
        select(ev.pos_x, ev.pos_y);
    }
    for(size_t i=0; i<LISTA.size(); i++){
        if(LISTA[i].size() > _SX/8){
            LISTA[i].erase (LISTA[i].begin()+((_SX-_SY-3)/8)-1, LISTA[i].end());
        }
    }
}

void Lista::draw()
{
    if(!focus)
        is_open=0;
    gout << move_to(_X, _Y) << color(0,0,0) << box(_SX, _SY);

    if(is_open && focusable && focus){
        gout << move_to(_X+1, _Y+1) << color(200,200,200) << box(_SX-2, _SY-2);
        gout << move_to(_X+_SX-_SY+1, _Y+1) << color(200,200,200) << box(_SY-2, _SY-2);
        gout << move_to(_X+_SX-_SY+1, _Y) << color(0,0,0) << line_to(_X+_SX-_SY+1, _Y+_SY-1);
        gout << move_to(_X+_SX-_SY/2 -4, _Y+_SY/2 +4) << color(0,0,0) << text("-");
        gout << move_to(_X, _Y+_SY) << color(0,0,0) << box(_SX, LS*20);
        gout << move_to(_X+1, _Y+_SY) << color(200,200,200) << box(_SX-2, LS*20 -1);
        gout << color(0,0,0);
        for(size_t i=0; i<LS; i++){
                if(act+i == selected){
                    gout << move_to(_X+4, _Y+_SY+(i)*20 +13) << color(255,0,0) << text(LISTA[act+i]);
                }
                else
                {
                    gout << move_to(_X+4, _Y+_SY+(i)*20 +13) << color(0,0,0) << text(LISTA[act+i]);
                }
                if(i>0){
                    gout << move_to(_X+2, _Y+_SY+(i)*20 -1) << color(150,150,150)  << line_to(_X+_SX-3, _Y+_SY+(i)*20 -1);
                }
        }

    }
    if(!is_open && focus && focusable){
        gout << move_to(_X+1, _Y+1) << color(200,200,200) << box(_SX-2, _SY-2);
        gout << move_to(_X+_SX-_SY+1, _Y+1) << color(200,200,200) << box(_SY-2, _SY-2);
        gout << move_to(_X+_SX-_SY+1, _Y) << color(0,0,0) << line_to(_X+_SX-_SY+1, _Y+_SY-1);
        gout << move_to(_X+_SX-_SY/2 -4, _Y+_SY/2 +4) << color(0,0,0) << text("+");
    }
    if(!focus && focusable){
        gout << move_to(_X+1, _Y+1) << color(160,160,160) << box(_SX-2, _SY-2);
        gout << move_to(_X+_SX-_SY+1, _Y+1) << color(160,160,160) << box(_SY-2, _SY-2);
        gout << move_to(_X+_SX-_SY+1, _Y) << color(0,0,0) << line_to(_X+_SX-_SY+1, _Y+_SY-1);
        gout << move_to(_X+_SX-_SY/2 -4, _Y+_SY/2 +4) << color(0,0,0) << text("+");
    }

    if(selected >= 0 && focusable){
        if(LISTA[selected].size() > (_SX-_SY-3)/8)
            LISTA[selected].erase (LISTA[selected].begin()+((_SX-_SY-3)/8)-1, LISTA[selected].end());
        gout << move_to(_X+4, _Y+_SY/2 +4) << color(0,0,0) << text(LISTA[selected]);
    }

    if(!focusable){
        gout << move_to(_X+1, _Y+1) << color(120,120,120) << box(_SX-2, _SY-2);
        gout << move_to(_X+_SX-_SY+1, _Y+1) << color(120,120,120) << box(_SY-2, _SY-2);
        gout << move_to(_X+_SX-_SY+1, _Y) << color(0,0,0) << line_to(_X+_SX-_SY+1, _Y+_SY-1);
        gout << move_to(_X+_SX-_SY/2 -4, _Y+_SY/2 +4) << color(0,0,0) << text("+");
    }
}

void Lista::button(int mx, int my)
{
    if(mx>=_X+_SX-_SY+1 && mx<=_X+_SX-1 && my>=_Y+1 && my<=_Y+_SY -2)
        is_open = !is_open;
}

void Lista::select(int mx, int my)
{
    if(mx>=_X && mx<=_X+_SX){
        for(int i=0; i<LS; i++){
            if(my>=_Y+_SY+i*20 && my<_Y+_SY+(i+1)*20)
                selected=act+i;
        }

    }
}

int Lista::get_val()
{
    return LISTA.size();
}

void Lista::add_line(std::string temp)
{
    if(!focusable)
        LISTA.erase (LISTA.begin());
    focusable=1;
    LISTA.push_back(temp);
    LS = LISTA.size();
    if(LS>orig_LS)
        LS=orig_LS;
    if(LISTA.size() > LS)
        rolling = 1;
    selected = 0;
    act = 0;
}

void Lista::del_line(int temp)
{
    if(temp > LISTA.size()){
        temp=-1;
    }
    if(temp<0 && LISTA.size()==1 && !ures){
        LISTA.erase (LISTA.begin());
        LISTA.push_back("empty list");
        focusable=0;
    }
    if(temp<0 && LISTA.size()>1){
        LISTA.erase (LISTA.begin()+selected);
    }
    if(LS > LISTA.size()){
        LS=LISTA.size();
        rolling = 0;
    }
        selected = 0;
        act = 0;
}

std::string Lista::get_line()
{
    return LISTA[selected];
}

void Lista::t_effects(event ev)
{
}
