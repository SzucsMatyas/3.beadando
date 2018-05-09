#ifndef MASTER_HPP_INCLUDED
#define MASTER_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"

class Master {
private:
    int XX, YY,
        t1X, t1Y, t1SX, t1SY,
        t2X, t2Y, t2SX, t2SY;
    double t1MHP, t1TOPHP, t1FRONTHP, t1BACKHP, t1DEG,
           t2MHP, t2TOPHP, t2FRONTHP, t2BACKHP, t2DEG;
    ;
public:
    Master(int XX, int YY,
           int t1X, int t1Y, int t1SX, int t1SY, double t1MHP,double t1SHP,
           int t2X, int t2Y, int t2SX, int t2SY, double t2MHP,double t2SHP);

    Master();

    virtual void shoot(std::string s);
    virtual bool hitdet(double msx, double msy);
//    int get_x();
//    int get_sx();
//    int get_y();
//    int get_sy();
};


#endif // MASTER_HPP_INCLUDED
