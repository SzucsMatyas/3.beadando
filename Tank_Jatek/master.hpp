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
    double t1MHP, t1TOPHP, t1FRONTHP, t1BACKHP, t1DEG,
           t2MHP, t2TOPHP, t2FRONTHP, t2BACKHP, t2DEG,
           wind;
    bool turn;
public:
    Master(int XX , int YY ,
           int t1X, int t1Y, int t1SX, int t1SY, double t1MHP,double t1SHP,
           int t2X, int t2Y, int t2SX, int t2SY, double t2MHP,double t2SHP);

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
};


#endif // MASTER_HPP_INCLUDED
