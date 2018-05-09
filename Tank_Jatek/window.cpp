#include "window.hpp"
#include "master.hpp"

using namespace std;
using namespace genv;

void Window::event_loop(int XX, int YY, bool fs, Master mester) {
    gout.open(XX,YY,fs);
    gout << refresh;
    event ev;
    int focus(-1);
    bool non;
    while(gin >> ev && ev.keycode!=key_escape) {
        for (size_t i=0;i<widgets.size();i++)
            widgets[i]->handle(ev);
        gout << move_to(0,0) << color(0,128,255) << box(XX,YY);
        for (Widget * w : widgets) {
            w->draw();
        }
        if (focus!=-1)
            widgets[focus]->draw();

        gout << refresh;
    }
}
