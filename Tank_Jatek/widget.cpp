#include "widget.hpp"
#include "graphics.hpp"
using namespace genv;

Widget::Widget(int x, int y, int sx, int sy) : _X(x), _Y(y), _SX(sx), _SY(sy)
{
    focus = 0;
    focusable = 1;
}

bool Widget::is_selected(int mx, int my)
{
    return mx>_X && mx<_X+_SX && my>_Y && my<_Y+_SY;
}

bool Widget::custom_is_selected(int mx, int my, int XX, int YY, int SXX, int SYY)
{
    return mx>XX && mx<XX+SXX && my>YY && my<YY+SYY;
}

void Widget::set_focus(bool temp)
{
    focus = temp;
}

bool Widget::get_focus()
{
    return focus;
}

bool Widget::get_focusable()
{
    return focusable;
}
