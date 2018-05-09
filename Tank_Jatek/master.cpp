#include "master.hpp"
#include "tank.hpp"
#include "graphics.hpp"
#include <iostream>
#include <cmath>

using namespace genv;

const double PI  =3.141592653589793238463;

Master::Master(int xx, int yy,
               int t1x, int t1y, int t1sx, int t1sy, double t1mhp, double t1shp,
               int t2x, int t2y, int t2sx, int t2sy, double t2mhp, double t2shp)
{
    XX=xx; YY=yy;
    t1DEG=t2DEG=20;

    t1X=t1x; t1Y=t1y; t1SX=t1sx; t1SY=t1sy; t1MHP=t1mhp; t1TOPHP=t1shp;
    t1BACKHP = t1FRONTHP = t1shp*1.5;

    t2X=t2x; t2Y=t2y; t2SX=t2sx; t2SY=t2sy; t2MHP=t2mhp; t2TOPHP=t2shp;
    t2BACKHP = t2FRONTHP = t2shp*1.5;
}

Master::Master(){}

void Master::shoot(std::string s){
    Tank *tank = new Tank();
//    ((_X+_SX/2)+(cos(deg*(PI/180))*_SX),(_Y+_SY/5)-(sin(deg*(PI/180)))*_SX)
    if(s=="t1"){
        double bx((t2X+t2SX/2)+(cos(t2DEG*(PI/180))*t2SX)), by((t2Y+t2SY/5)-(sin(t2DEG*(PI/180)))*t2SX), vx(cos(t2DEG*(PI/180))*6), vy(-sin(t2DEG*(PI/180))*6), gravity(0.03);
        event ev;
        gin.timer(5);
                std::cout << t2X << " " << t2SX << " " << t2DEG << std::endl;
        while(gin >> ev && !hitdet(bx, by)) {
            if(ev.type == ev_timer){
                tank->bullet_draw(bx,by);
                vy += gravity;
                bx += vx;
                by += vy;
            }
        }
    }
    if(s=="t2"){
        double bx((t1X+t1SX/2)-(cos(t1DEG*(PI/180))*t1SX)-6), by((t1Y+t1SY/5)-(sin(t1DEG*(PI/180)))*t1SX), vx(cos(t1DEG*(PI/180))*6), vy(-sin(t1DEG*(PI/180))*6), gravity(0.03);
        event ev;
        gin.timer(5);
//                std::cout << t1X << " " << t1Y << " " << t1SX << " " << t1SY << " " << t1DEG << std::endl;
        while(gin >> ev && !hitdet(bx, by)) {
            if(ev.type == ev_timer){
                tank->bullet_draw(bx,by);
                vy += gravity;
                bx -= vx;
                by += vy;
            }
        }
    }

}

bool Master::hitdet(double bx, double by){
    if(bx<0 || bx>XX-6 || by > YY-6){
        return 1;
    }else
        return 0;
}
