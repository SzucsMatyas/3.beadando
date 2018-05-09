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
//    gin.timer(40);
    while(gin >> ev && ev.keycode!=key_escape) {
//        if (ev.type == ev_mouse && ev.button==btn_left) {
//            non = 1;
//            for (size_t l=0;l<widgets.size();l++) {
//                widgets[l]->set_focus(0);
//            }
//            for (size_t i=0;i<widgets.size();i++) {
//                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y)) {
//                        focus = i;
//                        non = 0;
//                }
//            }
//            if(non)
//                focus = -1;
//        }
//        if(ev.keycode == -key_tab){
//            if(focus >= 0){
//                widgets[focus]->set_focus(0);
//                if(focus+1>=widgets.size())
//                    focus=0;
//                else
//                    focus++;
//
//                while(!widgets[focus]->get_focusable()){
//                    if(focus+1>=widgets.size())
//                        focus=0;
//                    else
//                        focus++;
//                }
//            }else{
//                focus = 0;
//
//            }
//            widgets[focus]->set_focus(1);
//        }
//        if (focus!=-1) {
//            widgets[focus]->handle(ev);
//        }
        for (size_t i=0;i<widgets.size();i++)
            widgets[i]->handle(ev);
        gout << move_to(0,0) << color(0,128,255) << box(XX,YY);
        for (Widget * w : widgets) {
            w->draw();
        }
//        if(ev.button==btn_left)
//            widgets[1]->t_effects(XX,YY,widgets[0]->get_X(), widgets[0]->get_Y(),
//                                    widgets[0]->get_SX(),
//                                    widgets[0]->get_SY(),
//                                    widgets[0]->get_top(),
//                                    widgets[0]->get_front(),
//                                    widgets[0]->get_back());
        if (focus!=-1)
            widgets[focus]->draw();

        gout << refresh;
    }
}
