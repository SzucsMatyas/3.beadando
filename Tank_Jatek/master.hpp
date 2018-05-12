#ifndef MASTER_HPP_INCLUDED
#define MASTER_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include <vector>
#include <iostream>
#include <stdlib.h>

class Master {
private:
    int XX, YY,
        t1X, t1Y, t1SX, t1SY,
        t2X, t2Y, t2SX, t2SY;
    double t1MHP, t1TOPHP, t1FRONTHP, t1BACKHP, t1DEG, t1STARTV,
           t2MHP, t2TOPHP, t2FRONTHP, t2BACKHP, t2DEG, t2STARTV,
           wind;
    bool turn;
public:
    Master(int XX , int YY ,
           int t1x, int t1y, int t1sx, int t1sy, double t1mhp, double t1shp, double t1startv,
           int t2x, int t2y, int t2sx, int t2sy, double t2mhp, double t2shp, double t2startv);

    virtual void shoot(std::vector<double>& eredmeny, std::string s);
    virtual bool hitdet(double msx, double msy, std::string player, bool& hit, bool& out);
    virtual void set_turn();
    virtual bool get_turn(){return turn;};
    virtual void set_wind()
    {
        double temp=rand()%50 -25;
        wind=temp/10;
//        wind=0;
    };
    virtual double get_wind(){return wind;};
    virtual void set_deg(int DEG, std::string name);
    virtual void set_startv(double startv, std::string name)
    {
        if(name == "startv1")
            t1STARTV=3*startv;
        if(name == "startv2")
            t2STARTV=3*startv;
    }
};


#endif // MASTER_HPP_INCLUDED
