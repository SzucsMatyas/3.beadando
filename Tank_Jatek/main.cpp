#include "graphics.hpp"
#include "widget.hpp"
#include "szamolo.hpp"
#include "lista.hpp"
#include "pushbutton.hpp"
#include "window.hpp"
#include "textbox.hpp"
#include "statictext.hpp"
#include "tank.hpp"
#include "mapdraw.hpp"
#include "clouds.hpp"
#include "master.hpp"
#include <vector>
#include <sstream>
#include <istream>
#include <iostream>

using namespace std;

class MyWindow : public Window {
public:
    Tank        * tank1;
    Tank        * tank2;
    PushButton  * pb1;
    PushButton  * pb2;
    Szamolo     * deg1;
    Szamolo     * deg2;
//    MapDraw     * ground;
//    Clouds      * cloud1;

    MyWindow(int XX, int YY, Master mester) ;
    void shoot(int t, Master mester) {
        if(t==1)
            mester.shoot("t1");
        if(t==2)
            mester.shoot("t2");
    }
};

MyWindow::MyWindow(int XX, int YY, Master mester){

    tank1           = new Tank(XX-163,YY-60,63,40,20,6.66,204,0,0,'r');
    tank2           = new Tank(100,YY-60,63,40,20,6.66,0,102,204,'l');
    pb1             = new PushButton(10,10,60,40,"lövés",[this,mester](){this->shoot(1, mester);});
    pb2             = new PushButton(XX-140,10,60,40,"lövés",[this,mester](){this->shoot(2, mester);});
    deg1            = new Szamolo(80,10,60,40,0,0,135,"deg1");
    deg2            = new Szamolo(XX-70,10,60,40,0,0,135,"deg2");
//    ground          = new MapDraw(0,YY-19,XX,19);
//    cloud1          = new Clouds(10,20,200,60);

    widgets.push_back(tank1);
    widgets.push_back(tank2);
    widgets.push_back(pb1);
    widgets.push_back(pb2);
    widgets.push_back(deg1);
    widgets.push_back(deg2);

//    widgets.push_back(ground);

//    widgets.push_back(cloud1);

};

void windowdata(int& XX, int& YY, bool& fs){
    ifstream be("felbontas.txt");
    be >> XX >> YY >> fs;
}

int main()
{
    int XX,YY;
    bool fs;
    windowdata(XX,YY,fs);

    Master mester( XX, YY,                           //window
                   XX-163,   YY-60,63,40,20,6.66,    //tank1
                   100,      YY-60,63,40,20,6.66     //tank2
                 );

    MyWindow *mywindow = new MyWindow(XX,YY, mester);
    mywindow->event_loop(XX,YY,fs, mester);
    return 0;
}
