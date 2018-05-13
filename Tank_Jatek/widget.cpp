#include "widget.hpp"
#include "graphics.hpp"
#include <vector>
#include <time.h>
#include <stdlib.h>



using namespace genv;

Widget::Widget(double x, double y, int sx, int sy) : _X(x), _Y(y), _SX(sx), _SY(sy)
{
    focus = 0;
    focusable = 1;
    hovered = 0;
}

Widget::Widget(): _X(0), _Y(0), _SX(0), _SY(0)
{
    focus = 0;
    focusable = 0;
    hovered = 0;
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

void Widget::draw(int r, int g, int b, int XX, int YY, int SIZE)
{
    double temp_X(_X), temp_Y(_Y), temp_SX(_SX), temp_SY(_SY);
    if(_Y<0)
        temp_Y=0;
    if(_Y>YY-SIZE)
        temp_SY=YY-_Y;
    if(_X<0)
        temp_X=0;
    if(_X>XX-SIZE)
        temp_SX=XX-_X;
    gout << move_to(temp_X,temp_Y) << color(r,g,b) << box(temp_SX,temp_SY);
}
int Widget::get_val(){return -1;}

void Widget::particle_effect(double bx, double by, double vxb, double vyb, int num, int XX, int YY, std::vector<Widget*> widgets, int R, int G, int B, int SIZE)
{
    std::vector<Particle> particles;
    for(int i=0; i<num; i++){
        double tvx = (rand()%500 -250);//100 +vx;
        tvx /= 150;
        double tvy = (rand()%250 -500);//100 +vx;
        tvy /= 100;
        tvy += vyb;
        tvx += vxb/5;
        if(bx<0)
            bx=0;
        if(bx>XX-SIZE)
            bx=XX-SIZE;
        Particle t(bx,by,SIZE,SIZE);
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
    }
    double gravity(0.2);
    event ev;
    gin.timer(10);
    while(gin >> ev && particles.size()>0) {
        if(ev.type==ev_timer){
            for(size_t i=0; i<particles.size(); i++){
                particles[i].set_vy(particles[i].get_vy()+gravity);
                particles[i]._Y+=particles[i].get_vy();
                particles[i]._X+=particles[i].get_vx();
                if(particles[i]._X+SIZE<0 || particles[i]._X>XX || particles[i]._Y > YY)
                    particles.erase (particles.begin()+i);
            }
            gout << move_to(0,0) << color(102,178,255) << box(XX,YY);
            for (Widget * w : widgets) {
                w->draw();
            }
            for(size_t i=0; i<particles.size(); i++){
                particles[i].draw(particles[i].get_r(),particles[i].get_g(),particles[i].get_b(),XX,YY,SIZE);
            }
            gout << refresh;
        }
    }
}

void Widget::blood_effect(double bx, double by, double vxb, double vyb, int num, int XX, int YY, std::vector<Widget*> widgets, int R, int G, int B, int SIZE)
{
    std::vector<Particle> particles;
    Particle garbage(-60,-60,0,0);
    particles.push_back(garbage);
    int counter(0);
    double gravity(0.2);
    event ev;
    gin.timer(10);
    while(gin >> ev && ev.type != ev_key && ev.button != btn_left && ev.button != btn_right && particles.size()>0){
        if(ev.type==ev_timer){
            if(counter<1000){
                for(int i=0; i<num; i++){
                    double tvx = (rand()%500 -250);//100 +vx;
                    tvx /= 150;
                    double tvy = (rand()%250 -500);//100 +vx;
                    tvy /= 100;
                    tvy += vyb;
                    tvx += vxb/5;
                    Particle t(bx+ rand()%60 - 30,by,SIZE,SIZE);
                        t.set_vy(tvy);
                        t.set_vx(tvx);
                        if(R>0 && R<=255)
                            t.set_r(R+rand()%50 -25);
                        if(G>0 && G<=255)
                            t.set_g(G+rand()%50 -25);
                        if(B>0 && B<=255)
                            t.set_b(B+rand()%50 -25);

                        if(t.get_r()<0 || R<=0)
                            t.set_r(0);
                        if(t.get_r()>255 || R>255)
                            t.set_r(255);

                        if(t.get_g()<0 || G<=0)
                            t.set_g(0);
                        if(t.get_g()>255 || G>255)
                            t.set_g(255);

                        if(t.get_b()<0 || B<=0)
                            t.set_b(0);
                        if(t.get_b()>255 || B>255)
                            t.set_b(255);
                    particles.push_back(t);
                }
            }
            for(size_t i=0; i<particles.size(); i++){
                particles[i].set_vy(particles[i].get_vy()+gravity);
                particles[i]._Y+=particles[i].get_vy();
                particles[i]._X+=particles[i].get_vx();
                if(particles[i]._X+SIZE<0 || particles[i]._X>XX || particles[i]._Y > YY)
                    particles.erase (particles.begin()+i);
            }
            gout << move_to(0,0) << color(102,178,255) << box(XX,YY);
            for (Widget * w : widgets) {
                w->draw();
            }
            for(size_t i=0; i<particles.size(); i++){
                particles[i].draw(particles[i].get_r(),particles[i].get_g(),particles[i].get_b(),XX,YY,SIZE);
            }
            counter++;
            gout << refresh;
        }
    }
}

void Widget::bullet_draw(double bx, double by, int XX, int YY, std::vector<Widget*> widgets)
{
    gout << move_to(0,0) << color(102,178,255) << box(XX,YY);
    for (Widget * w : widgets) {
        w->draw();
    }
    if(by>=0){
        gout << move_to(bx,by) << color(0,  0,  0) << box(6,6);
    }
    if(by<0){
        gout << move_to(bx, 0) << color(0,  0,255) << box(6,6);
    }
    gout<<refresh;
}
