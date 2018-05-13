#include "graphics.hpp"
#include "widget.hpp"
#include "szamolo.hpp"
#include "lista.hpp"
#include "pushbutton.hpp"
#include "window.hpp"
#include "textbox.hpp"
#include "statictext.hpp"
#include "tank.hpp"
#include "clouds.hpp"
#include "master.hpp"
#include <vector>
#include <sstream>
#include <istream>
#include <time.h>
#include <stdlib.h>

using namespace std;

class MyWindow : public Window {
public:
    Tank        * tank1;
    PushButton  * pb1;
    Szamolo     * deg1;
    Szamolo     * startv1;
    StaticText  * pdec1;
    StaticText  * deg1sign;
    StaticText  * startv1sign;

    Tank        * tank2;
    PushButton  * pb2;
    Szamolo     * deg2;
    Szamolo     * startv2;
    StaticText  * pdec2;
    StaticText  * deg2sign;
    StaticText  * startv2sign;

    StaticText  * turn;
    Widget      * ground;
    Widget      * wall;
    Clouds      * cloud1;
    PushButton  * newgame;

    MyWindow(int XX, int YY, Master& ms) ;
    void shoot(int t, Master& ms, int XX, int YY) {
        vector<double> eredmeny(10,0);
        if(ms.get_main("tank1")>0 && ms.get_main("tank2")>0){
            if(t==1 && ms.get_turn() && pb1->get_focusable()){
                ms.shoot(eredmeny, "t1",widgets);
                tank2->set_fronthp(eredmeny[0]);
                tank2->set_backhp(eredmeny[1]);
                tank2->set_tophp(eredmeny[2]);
                tank2->set_mainhp(eredmeny[3]);
                if(eredmeny[8]==0 && eredmeny[9]==0)
                    tank1->particle_effect(eredmeny[4]-10,eredmeny[5],eredmeny[6],eredmeny[7],20,XX,YY,widgets,153,76,0,6);
                if(eredmeny[8]==1 && eredmeny[9]==0)
                    tank1->particle_effect(eredmeny[4]-10,eredmeny[5],eredmeny[6],eredmeny[7],60,XX,YY,widgets,204,1,1,10);
                if(eredmeny[9]==1)
                    tank1->particle_effect(eredmeny[4],eredmeny[5],-eredmeny[6],0,5,XX,YY,widgets,254,254,254,6);
                ms.set_turn();
                ms.set_wind();
                pb1->set_focusable(0);
                deg1->set_focusable(0);
                startv1->set_focusable(0);
                pb2->set_focusable(1);
                deg2->set_focusable(1);
                startv2->set_focusable(1);
                cloud1->set_wind(ms.get_wind());
            }
            if(t==2 && !ms.get_turn() && pb2->get_focusable()){
                ms.shoot(eredmeny, "t2",widgets);
                tank1->set_fronthp(eredmeny[0]);
                tank1->set_backhp(eredmeny[1]);
                tank1->set_tophp(eredmeny[2]);
                tank1->set_mainhp(eredmeny[3]);
                if(eredmeny[8]==0 && eredmeny[9]==0)
                    tank1->particle_effect(eredmeny[4]+15,eredmeny[5],eredmeny[6],eredmeny[7],20,XX,YY,widgets,153,76,0,6);
                if(eredmeny[8]==1 && eredmeny[9]==0)
                    tank1->particle_effect(eredmeny[4]+15,eredmeny[5],eredmeny[6],eredmeny[7],60,XX,YY,widgets,204,1,1,10);
                if(eredmeny[9]==1)
                    tank1->particle_effect(eredmeny[4],eredmeny[5],-eredmeny[6],0,5,XX,YY,widgets,254,254,254,6);
                ms.set_turn();
                ms.set_wind();
                pb1->set_focusable(1);
                deg1->set_focusable(1);
                startv1->set_focusable(1);
                pb2->set_focusable(0);
                deg2->set_focusable(0);
                startv2->set_focusable(0);
                cloud1->set_wind(ms.get_wind());
            }
            if(ms.get_turn())
                turn->set_text("Player 1");
            if(!ms.get_turn())
                turn->set_text("Player 2");
        }
        if(ms.get_main("tank1")==0 || ms.get_main("tank2")==0){
            deg1->set_focusable(0);
            deg2->set_focusable(0);
            startv1->set_focusable(0);
            startv2->set_focusable(0);
            pb1->set_focusable(0);
            pb2->set_focusable(0);
            newgame->set_focusable(1);
            if(ms.get_main("tank1")==0){
                turn->set_text("player 2 won!");
                tank1->blood_effect(ms.get_x("tank1")+ms.get_sx("tank1")/2 -7,ms.get_y("tank1")+ms.get_sy("tank1")/2 -7,3,-5,3,XX,YY,widgets,255,150,1,5);
            }
            if(ms.get_main("tank2")==0){
                turn->set_text("player 1 won!");
                tank2->blood_effect(ms.get_x("tank2")+ms.get_sx("tank2")/2 -7,ms.get_y("tank2")+ms.get_sy("tank2")/2 -7,-3,-5,3,XX,YY,widgets,255,150,1,5);
            }
        }
    }
    void degmanip(int t, Master& ms)
    {
        if(t==1 && ms.get_turn()){
            ms.set_deg(deg1->get_ct(), "deg1");
            tank1->set_deg(deg1->get_ct());
        }
        if(t==2 && !ms.get_turn()){
            ms.set_deg(deg2->get_ct(), "deg2");
            tank2->set_deg(deg2->get_ct());
        }
    }
    void startvmanip(int t, Master& ms)
    {
        if(t==1 && ms.get_turn()){
            ms.set_startv(startv1->get_ct(), "startv1");
        }
        if(t==2 && !ms.get_turn()){
            ms.set_startv(startv2->get_ct(), "startv2");
        }
    }
    void new_game(Master& ms)
    {
        ms.reset(20,10,20,10);
        deg1->set_ct(20);
        deg2->set_ct(20);
        startv1->set_ct(3);
        startv2->set_ct(3);
        tank1->reset(20,10);
        tank2->reset(20,10);

        deg1->set_focusable(1);
        startv1->set_focusable(1);
        pb1->set_focusable(1);

        if(ms.get_turn())
            turn->set_text("Player 1");
        if(!ms.get_turn())
            turn->set_text("Player 2");

        newgame->set_focusable(0);
    }
};

MyWindow::MyWindow(int XX, int YY, Master& ms){

    tank1           = new Tank(18,YY-60,63,40,20,10,0,102,204,'l');
    pb1             = new PushButton(10,10,60,50,"shoot",[this,&ms, XX, YY](){this->shoot(1, ms, XX, YY);});
    deg1            = new Szamolo(80,30,60,30,20,0,135,[this,&ms](){this->degmanip(1, ms);});
    startv1         = new Szamolo(150,30,60,30,3,1,5,[this,&ms](){this->startvmanip(1, ms);});
    pdec1           = new StaticText(0,YY-20,100,20,"Player 1");
    deg1sign        = new StaticText(80,10,60,20,"Angle");
    startv1sign     = new StaticText(150,10,60,20,"Power");

    tank2           = new Tank(XX-80,YY-60,63,40,20,10,204,0,0,'r');
    pb2             = new PushButton(XX-210,10,60,50,"shoot",[this,&ms, XX, YY](){this->shoot(2, ms, XX, YY);});
    deg2            = new Szamolo(XX-140,30,60,30,20,0,135,[this,&ms](){this->degmanip(2, ms);});
    startv2         = new Szamolo(XX-70,30,60,30,3,1,5,[this,&ms](){this->startvmanip(2, ms);});
    pdec2           = new StaticText(XX-100,YY-20,100,20,"Player 2");
    deg2sign        = new StaticText(XX-140,10,60,20,"Angle");
    startv2sign     = new StaticText(XX-70,10,60,20,"Power");

    turn            = new StaticText(XX/2 -100,10,200,40,"Player 1");
    ground          = new Widget(0,YY-20,XX,20);
    cloud1          = new Clouds(XX/2 -300,100,400,100,XX,YY);
    wall            = new Widget(XX/2 -100, YY-100,200,80);
    newgame         = new PushButton(XX/2 -80, YY-80,160,60,"new game",[this,&ms](){this->new_game(ms);});

    pb2->set_focusable(0);
    deg2->set_focusable(0);
    startv2->set_focusable(0);
    ground->set_focusable(0);
    wall->set_focusable(0);
    newgame->set_focusable(0);
    cloud1->set_wind(ms.get_wind());

    widgets.push_back(tank1);
    widgets.push_back(tank2);
    widgets.push_back(pb1);
    widgets.push_back(pb2);
    widgets.push_back(deg1);
    widgets.push_back(deg2);
    widgets.push_back(startv1);
    widgets.push_back(startv2);
    widgets.push_back(deg1sign);
    widgets.push_back(deg2sign);
    widgets.push_back(startv1sign);
    widgets.push_back(startv2sign);
    widgets.push_back(turn);
    widgets.push_back(ground);
    widgets.push_back(wall);
    widgets.push_back(pdec1);
    widgets.push_back(pdec2);
    widgets.push_back(cloud1);
    widgets.push_back(newgame);

};

void windowdata(int& XX, int& YY, bool& fs){
    ifstream be("felbontas.txt");
    be >> XX >> YY >> fs;
}

int main()
{
    srand(time(NULL));
    int XX,YY;
    bool fs;
    windowdata(XX,YY,fs);

    Master mester( XX, YY,                          //window
                   18,      YY-60,63,40,20,10,3,    //tank1
                   XX-80,   YY-60,63,40,20,10,3,    //tank2
                   XX/2 -100, YY-100,200,80          //wall
                 );
    mester.set_wind();
    MyWindow *mywindow = new MyWindow(XX,YY, mester);
    mywindow->event_loop(XX,YY,fs, mester);
    return 0;
}
