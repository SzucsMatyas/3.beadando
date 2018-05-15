#ifndef MASTER_HPP_INCLUDED
#define MASTER_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include <vector>
#include <stdlib.h>

class Master {
private:
    int XX, YY,
        t1X, t1Y, t1SX, t1SY,
        t2X, t2Y, t2SX, t2SY,
        wallX, wallY, wallSX, wallSY;
    double t1MHP, t1TOPHP, t1FRONTHP, t1BACKHP, t1DEG, t1STARTV,
           t2MHP, t2TOPHP, t2FRONTHP, t2BACKHP, t2DEG, t2STARTV,
           wind;
    bool turn;
public:
    Master(int XX , int YY ,
           int t1x, int t1y, int t1sx, int t1sy, double t1mhp, double t1shp, double t1startv,
           int t2x, int t2y, int t2sx, int t2sy, double t2mhp, double t2shp, double t2startv,
           int wallx, int wally, int wallsx, int wallsy);

    virtual void reset (double t1mhp, double t1shp, double t2mhp, double t2shp);
    virtual void shoot(std::vector<double>& eredmeny, std::string s, std::vector<Widget*> widgets);
    virtual bool hitdet(double msx, double msy, std::string player, bool& hit, bool& out);
    virtual void set_turn();
    virtual bool get_turn(){return turn;};
    virtual void set_wind()
    {
        double temp=rand()%50 -25;
        wind=temp/10;
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
    virtual double get_main(std::string name)
    {
        if(name == "tank1")
            return t1MHP;
        if(name == "tank2")
            return t2MHP;
        return -1;
    }
    virtual double get_x(std::string name)
    {
        if(name == "tank1")
            return t1X;
        if(name == "tank2")
            return t2X;
        return -1;
    }
    virtual double get_y(std::string name)
    {
        if(name == "tank1")
            return t1Y;
        if(name == "tank2")
            return t2Y;
        return -1;
    }
    virtual double get_sx(std::string name)
    {
        if(name == "tank1")
            return t1SX;
        if(name == "tank2")
            return t2SX;
        return -1;
    }
    virtual double get_sy(std::string name)
    {
        if(name == "tank1")
            return t1SY;
        if(name == "tank2")
            return t2SY;
        return -1;
    }
};


#endif // MASTER_HPP_INCLUDED
