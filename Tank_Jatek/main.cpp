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
    Master      * mester;
//    MapDraw     * ground;
//    Clouds      * cloud1;

    MyWindow(int XX, int YY) ;
    void shoot(int t) {
        if(t==1)
            cout<< "1-es loves" << endl;
        if(t==2)
            cout<< "2-es loves" << endl;

    }
};

MyWindow::MyWindow(int XX, int YY){

    tank1           = new Tank(XX-163,YY-60,63,40,20,6.66,204,0,0,'r');
    tank2           = new Tank(100,YY-60,63,40,20,6.66,0,102,204,'l');
    pb1             = new PushButton(10,10,60,40,"lövés",[this](){this->shoot(1);});
    pb2             = new PushButton(XX-70,10,60,40,"lövés",[this](){this->shoot(2);});
//    ground          = new MapDraw(0,YY-19,XX,19);
//    cloud1          = new Clouds(10,20,200,60);

    widgets.push_back(tank1);
    widgets.push_back(tank2);
    widgets.push_back(pb1);
    widgets.push_back(pb2);

    mester          = new Master(widgets, XX, YY);
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
    MyWindow *mywindow = new MyWindow(XX,YY);
    mywindow->event_loop(XX,YY,fs, mester);
    return 0;
}
