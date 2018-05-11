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
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

class MyWindow : public Window {
public:
    Tank        * tank1;
    Tank        * tank2;
    PushButton  * pb1;
    PushButton  * pb2;
    Szamolo     * deg1;
    Szamolo     * deg2;
    StaticText  * turn;
    Widget      * ground;
    StaticText  * pdec1;
    StaticText  * pdec2;
    Clouds      * cloud1;

    MyWindow(int XX, int YY, Master& ms) ;
    void shoot(int t, Master& ms, int XX, int YY) {
        if(t==1 && !ms.get_turn()){
            vector<double> eredmeny(10,0);
            ms.shoot(eredmeny, "t1");
            tank1->set_fronthp(eredmeny[0]);
            tank1->set_backhp(eredmeny[1]);
            tank1->set_tophp(eredmeny[2]);
            tank1->set_mainhp(eredmeny[3]);
            if(eredmeny[8]==0 && eredmeny[9]==0)
                tank1->particle_effect(eredmeny[4]+15,eredmeny[5],eredmeny[6],eredmeny[7],20,XX,YY,widgets,153,76,0);
            if(eredmeny[8]==1 && eredmeny[9]==0)
                tank1->particle_effect(eredmeny[4]+15,eredmeny[5],eredmeny[6],eredmeny[7],60,XX,YY,widgets,204,1,1);
            ms.set_turn();
            ms.set_wind();
            cloud1->set_wind(ms.get_wind());
        }
        if(t==2 && ms.get_turn()){
            vector<double> eredmeny(10,0);
            ms.shoot(eredmeny, "t2");
            tank2->set_fronthp(eredmeny[0]);
            tank2->set_backhp(eredmeny[1]);
            tank2->set_tophp(eredmeny[2]);
            tank2->set_mainhp(eredmeny[3]);
            if(eredmeny[8]==0 && eredmeny[9]==0)
                tank1->particle_effect(eredmeny[4]-10,eredmeny[5],eredmeny[6],eredmeny[7],20,XX,YY,widgets,153,76,0);
            if(eredmeny[8]==1 && eredmeny[9]==0)
                tank1->particle_effect(eredmeny[4]-10,eredmeny[5],eredmeny[6],eredmeny[7],60,XX,YY,widgets,204,1,1);
            ms.set_turn();
            ms.set_wind();
            cloud1->set_wind(ms.get_wind());
        }
        if(ms.get_turn())
            turn->set_text("Player 2");
        if(!ms.get_turn())
            turn->set_text("Player 1");
    }
};

MyWindow::MyWindow(int XX, int YY, Master& ms){

    tank1           = new Tank(XX-80,YY-60,63,40,20,10,204,0,0,'r');
    tank2           = new Tank(18,YY-60,63,40,20,10,0,102,204,'l');
    pb1             = new PushButton(10,10,60,40,"shoot",[this,&ms, XX, YY](){this->shoot(1, ms, XX, YY);});
    pb2             = new PushButton(XX-140,10,60,40,"shoot",[this,&ms, XX, YY](){this->shoot(2, ms, XX, YY);});
    deg1            = new Szamolo(80,10,60,40,0,0,135,"deg1");
    deg2            = new Szamolo(XX-70,10,60,40,0,0,135,"deg2");
    turn            = new StaticText(XX/2 -100,10,200,40,"Player 1");
    ground          = new Widget(0,YY-20,XX,20);
    pdec1           = new StaticText(0,YY-20,20,20,"P1");
    pdec2           = new StaticText(XX-20,YY-20,20,20,"P2");
    cloud1          = new Clouds(XX/2 -300,100,400,100,XX,YY);

    cloud1->set_wind(ms.get_wind());

    widgets.push_back(tank1);
    widgets.push_back(tank2);
    widgets.push_back(pb1);
    widgets.push_back(pb2);
    widgets.push_back(deg1);
    widgets.push_back(deg2);
    widgets.push_back(turn);
    widgets.push_back(ground);
    widgets.push_back(pdec1);
    widgets.push_back(pdec2);
    widgets.push_back(cloud1);

};

void windowdata(int& XX, int& YY, bool& fs){
    ifstream be("felbontas.txt");
    be >> XX >> YY >> fs;
}

int main()
{
    srand(time(NULL));
//    for(int i=0; i<20; i++)
//        cout << rand()%5 -2 << endl;
    int XX,YY;
    bool fs;
    windowdata(XX,YY,fs);

    Master mester( XX, YY,                        //window
                   XX-80,   YY-60,63,40,20,10,    //tank1
                   18,      YY-60,63,40,20,10     //tank2
                 );
    mester.set_wind();
    MyWindow *mywindow = new MyWindow(XX,YY, mester);
    mywindow->event_loop(XX,YY,fs, mester);
    return 0;
}
