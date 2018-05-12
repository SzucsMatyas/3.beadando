#include "window.hpp"
#include "master.hpp"

using namespace std;
using namespace genv;

void Window::event_loop(int XX, int YY, bool fs, Master mester) {
    gout.open(XX,YY,fs);
    gout << refresh;
    event ev;
    gin.timer(40);
    int focus(-1);
    bool non;
    while(gin >> ev && ev.keycode!=key_escape) {
        if (ev.type == ev_mouse) {
            for (size_t l=0;l<widgets.size();l++) {
                widgets[l]->set_hovered(0);
            }
            for (size_t i=0;i<widgets.size();i++) {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y) && widgets[i]->get_focusable()) {
                    widgets[i]->set_hovered(1);
                }
            }
        }
        if (ev.type == ev_mouse && ev.button==btn_left) {
            non = 1;
            if(focus!=-1){
                widgets[focus]->set_focus(0);
                widgets[focus]->draw();
            }
            for (size_t l=0;l<widgets.size();l++) {
                widgets[l]->set_focus(0);
            }
            for (size_t i=0;i<widgets.size();i++) {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y) && widgets[i]->get_focusable()) {
                    focus = i;
                    non = 0;
                }
            }
            if(non)
                focus = -1;
        }
        if(ev.keycode == -key_tab){
            if(focus < 0 || !widgets[focus]->get_focusable())
                focus = 0;
            widgets[focus]->set_focus(0);
            if(focus+1>=widgets.size())
                focus=0;
            else
                focus++;

            while(!widgets[focus]->get_focusable()){
                if(focus+1>=widgets.size())
                    focus=0;
                else
                    focus++;
            }
            widgets[focus]->set_focus(1);
        }
        if(ev.type==ev_timer){
            gout << move_to(0,0) << color(102,178,255) << box(XX,YY);
            for (Widget * w : widgets) {
                w->draw();
            }
        }
        if (focus!=-1)
            widgets[focus]->draw();
        if (focus!=-1) {
            widgets[focus]->handle(ev);
        }

        gout << refresh;
    }
}
