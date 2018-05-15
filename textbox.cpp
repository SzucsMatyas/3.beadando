#include "textbox.hpp"
#include "graphics.hpp"
#include <string>

using namespace genv;

TextBox::TextBox(int x, int y, int sx, int sy, std::string t, std::function<void()> functor)
    : Widget(x,y,sx,sy)
{
    _firstchecked=false;
    txt=t;
    _functor=functor;
}

void TextBox::handle(event ev)
{
    if (is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left) {
        focus = 1;

        if(_firstchecked==0){
            txt = "";
            _firstchecked = 1;
        }
    }
    if (!is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left){
        focus = 0;
    }
    if (focus && ev.keycode == +key_backspace){
        del_text();
    }
    if (focus && ev.keycode!=key_backspace && ev.keycode>=32 && ev.keycode<=256){
        add_text(ev.keycode);
    }
    if(focus && ev.keycode==key_enter)
        action();
}

void TextBox::draw()
{
    gout << move_to(_X, _Y) << color(0,0,0) << box(_SX, _SY);
    if (focus){
        gout << move_to(_X+1, _Y+1) << color(200,200,200) << box(_SX-2, _SY-2);
        gout << move_to(_X+4, _Y+_SY/2 +4) << color(0,0,0) << text(txt);
        gout << move_to(_X+4+txt.size()*8, _Y+4) << line_to(_X+4+txt.size()*8, _Y+_SY-5);
    }
    if (!focus && !_firstchecked){
        gout << move_to(_X+1, _Y+1) << color(160,160,160) << box(_SX-2, _SY-2);
        gout << move_to(_X+4, _Y+_SY/2 +4) << color(60,60,60) << text(txt);
    }
    if (!focus && _firstchecked){
        gout << move_to(_X+1, _Y+1) << color(160,160,160) << box(_SX-2, _SY-2);
        gout << move_to(_X+4, _Y+_SY/2 +4) << color(0,0,0) << text(txt);
    }
}

void TextBox::add_text(char temp)
{
    if(txt.size()*8 < _SX-16)
        txt+=(char)temp;
}

void TextBox::del_text()
{
    if(txt.size()>0)
        txt.erase (txt.end()-1);
}

std::string TextBox::get_text()
{
    if(_firstchecked && txt.length()>0){
        return txt;
    }else{
        return "error";
    }
}

void TextBox::set_text(std::string temp)
{
    txt=temp;
}

int TextBox::get_val()
{
    return -1;
}

void TextBox::set_focus(bool temp)
{
    focus = temp;
    if(_firstchecked==0 && temp){
        txt = "";
        _firstchecked = 1;
    }
}

void TextBox::action(){
    _functor();
}

void TextBox::t_effects(event ev)
{
}
