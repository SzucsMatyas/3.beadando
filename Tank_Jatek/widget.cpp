#include "widget.hpp"
#include "graphics.hpp"
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iostream>


using namespace genv;

Widget::Widget(double x, double y, int sx, int sy) : _X(x), _Y(y), _SX(sx), _SY(sy)
{
    focus = 0;
    focusable = 1;
}

Widget::Widget(): _X(0), _Y(0), _SX(0), _SY(0)
{
    focus = 0;
    focusable = 0;
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

void Widget::handle(genv::event ev){}

void Widget::draw()
{
   gout << move_to(_X, _Y) << color(153,76,0) << box(_SX,_SY);
}

void Widget::draw(genv::event ev)
{
   gout << move_to(_X, _Y) << color(153,76,0) << box(_SX,_SY);
}

void Widget::draw(int r, int g, int b)
{
    gout << move_to(_X,_Y) << color(r,g,b) << box(_SX,_SY);
}
int Widget::get_val(){return -1;}

void Widget::particle_effect(double bx, double by, double vxb, double vyb, int num, int XX, int YY, std::vector<Widget*> widgets, int R, int G, int B)
{
//    std::cout << vx << std::endl;
//    srand (time(NULL));
    std::vector<Particle> particles;
    for(int i=0; i<num; i++){
        double tvx = (rand()%500 -250);//100 +vx;
        tvx /= 150;
        double tvy = (rand()%250 -500);//100 +vx;
        tvy /= 100;
        tvy += vyb;
        tvx += vxb/5;
        Particle t(bx,by,5,5);
        particles.push_back(t);
        particles[i].set_vy(tvy);
        particles[i].set_vx(tvx);
        if(R>0 && R<=255)
            particles[i].set_r(R+rand()%50 -25);
        if(G>0 && G<=255)
            particles[i].set_g(G+rand()%50 -25);
        if(B>0 && B<=255)
            particles[i].set_b(B+rand()%50 -25);

        if(particles[i].get_r()<0 || R<=0)
            particles[i].set_r(0);
        if(particles[i].get_r()>255 || R>255)
            particles[i].set_r(255);

        if(particles[i].get_g()<0 || G<=0)
            particles[i].set_g(0);
        if(particles[i].get_g()>255 || G>255)
            particles[i].set_g(255);

        if(particles[i].get_b()<0 || B<=0)
            particles[i].set_b(0);
        if(particles[i].get_b()>255 || B>255)
            particles[i].set_b(255);
//        std::cout << particles[i].get_r() << " " << particles[i].get_g() << " " << particles[i].get_b() << std::endl;
    }
    double gravity(0.2);
    event ev;
    gin.timer(10);
    while(gin >> ev && particles.size()>0) {
        if(ev.type==ev_timer){
            for(size_t i=0; i<particles.size(); i++){
                particles[i].set_vy(particles[i].get_vy()+gravity);
    //            std::cout << gravity << " " << Vx << " " << Vy << std::endl;
                particles[i]._Y+=particles[i].get_vy();
                particles[i]._X+=particles[i].get_vx();
                if(particles[i]._X<0 || particles[i]._X>XX-3 || particles[i]._Y > YY-3)
                    particles.erase (particles.begin()+i);
            }
            gout << move_to(0,0) << color(102,178,255) << box(XX,YY);
            for (Widget * w : widgets) {
//                std::cout << "dang" << std::endl;
                w->draw(ev);
            }
            for(size_t i=0; i<particles.size(); i++){
                particles[i].draw(particles[i].get_r(),particles[i].get_g(),particles[i].get_b());
            }
            gout << refresh;
        }
    }
}

void Widget::bullet_draw(double bx, double by)
{
    if(by>=0){
        gout << move_to(bx,by) << color(0,  0,  0) << box(6,6) << refresh;
        gout << move_to(bx,by) << color(102,178,255) << box(6,6) ;
    }
    if(by<0){
        gout << move_to(bx, 0) << color(0,  0,255) << box(6,6) << refresh;
        gout << move_to(bx, 0) << color(102,178,255) << box(6,6) ;
    }
}
