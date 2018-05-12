#include "master.hpp"
#include "tank.hpp"
#include "graphics.hpp"
#include <cmath>

using namespace genv;

const double PI  =3.141592653589793238463;

Master::Master(int xx, int yy,
               int t1x, int t1y, int t1sx, int t1sy, double t1mhp, double t1shp, double t1startv,
               int t2x, int t2y, int t2sx, int t2sy, double t2mhp, double t2shp, double t2startv,
               int wallx, int wally, int wallsx, int wallsy)
{
    turn=1;
    wind=0;

    XX=xx; YY=yy;
    t1DEG=t2DEG=20;

    t1X=t1x; t1Y=t1y; t1SX=t1sx; t1SY=t1sy; t1MHP=t1mhp; t1TOPHP=t1shp; t1STARTV=3*t1startv;
    t1BACKHP = t1FRONTHP = t1shp*2;

    t2X=t2x; t2Y=t2y; t2SX=t2sx; t2SY=t2sy; t2MHP=t2mhp; t2TOPHP=t2shp; t2STARTV=3*t2startv;
    t2BACKHP = t2FRONTHP = t2shp*2;

    wallX=wallx; wallY=wally; wallSX=wallsx; wallSY=wallsy;
}

void Master::reset (double t1mhp, double t1shp, double t2mhp, double t2shp)
{
    t1MHP=t1mhp; t1TOPHP=t1shp;
    t1BACKHP = t1FRONTHP = t1shp*2;

    t2MHP=t2mhp; t2TOPHP=t2shp;
    t2BACKHP = t2FRONTHP = t2shp*2;

    turn=1;

    t1DEG=t2DEG=20;
}

void Master::shoot(std::vector<double>& eredmeny, std::string s, std::vector<Widget*> widgets){
    Widget *temp = new Widget();
    bool hit(0);
    bool out(0);
    if(s=="t1"){
        double bx((t1X+t1SX/2)+(cos(t1DEG*(PI/180))*t1SX)+6), by((t1Y+t1SY/5)-(sin(t1DEG*(PI/180)))*t1SX), vx(cos(t1DEG*(PI/180))*t1STARTV), vy(-sin(t1DEG*(PI/180))*t1STARTV), gravity(0.03);
        event ev;
        gin.timer(1);
        while(gin >> ev && !hitdet(bx, by, "t1",hit,out)) {
            if(ev.type == ev_timer){
                temp->bullet_draw(bx,by,XX,YY,widgets);
                vx += wind/50;
                vy += gravity;
                bx += vx;
                by += vy;
            }
        }
        eredmeny[0]=t2FRONTHP;
        eredmeny[1]=t2BACKHP;
        eredmeny[2]=t2TOPHP;
        eredmeny[3]=t2MHP;
        eredmeny[4]=bx;
        eredmeny[5]=by;
        eredmeny[6]=vx;
        eredmeny[7]=-vy;
        eredmeny[8]=hit;
        eredmeny[9]=out;
    }
    if(s=="t2"){
        double bx((t2X+t2SX/2)-(cos(t2DEG*(PI/180))*t2SX)-12), by((t2Y+t2SY/5)-(sin(t2DEG*(PI/180)))*t2SX), vx(cos(t2DEG*(PI/180))*t2STARTV), vy(-sin(t2DEG*(PI/180))*t2STARTV), gravity(0.03);
        event ev;
        gin.timer(5);
        while(gin >> ev && !hitdet(bx, by, "t2",hit,out)) {
            if(ev.type == ev_timer){
                temp->bullet_draw(bx,by,XX,YY,widgets);
                vx -= wind/50;
                vy += gravity;
                bx -= vx;
                by += vy;
            }
        }
        eredmeny[0]=t1FRONTHP;
        eredmeny[1]=t1BACKHP;
        eredmeny[2]=t1TOPHP;
        eredmeny[3]=t1MHP;
        eredmeny[4]=bx;
        eredmeny[5]=by;
        eredmeny[6]=-vx;
        eredmeny[7]=-vy;
        eredmeny[8]=hit;
        eredmeny[9]=out;
    }
}

bool Master::hitdet(double bx, double by, std::string player, bool& hit, bool& out){
    if(bx<0 || bx>XX-6){
        out=1;
        return 1;
    }
    if(by > t1Y+t1SY || (bx<wallX+wallSX && bx>wallX-6 && by>wallY-6)){
        return 1;
    }
    if(player == "t1"){
        if(t2FRONTHP>0 && bx>=t2X+t2SX+8  && bx<= t2X+t2SX+t2SX/5 +2 && by>= t2Y-(t2SX/5)-9 && by<= t2Y-(t2SX/5)-3+t2SY+(t2SX/5)+4){
            if(t2FRONTHP-5<=0){
                t2FRONTHP=0;
            }else{
                t2FRONTHP-=5;
            }
            hit=1;
            return 1;
        }

        if(t2BACKHP>0 && bx>=t2X-(t2SX/5)-8 && bx<=t2X-(t2SX/5)-2 + t2SX/5 && by>= t2Y-(t2SX/5)-9 && by<= t2Y-(t2SX/5)-3+t2SY+(t2SX/5)){
            if(t2BACKHP-5<=0){
                t2BACKHP=0;
            }else{
                t2BACKHP-=5;
            }
            hit=1;
            return 1;
        }

        if(t2TOPHP>0 && bx<= t2X+t2SX && bx>=t2X && by<=t2Y-(t2SX/5)-3+(t2SX/5) && by>=t2Y-(t2SX/5)-9){
            if(t2TOPHP-5<=0){
                t2TOPHP=0;
            }else{
                t2TOPHP-=5;
            }
            hit=1;
            return 1;
        }

        if(bx<= t2X+t2SX && bx>= t2X-6 && by>=t2Y-6 && by<= t2Y+t2SY){
            if(t2MHP-5<=0){
                t2MHP=0;
            }else{
                t2MHP-=5;
//                std::cout << t2MHP << " " << t2TOPHP << " " << t2FRONTHP << " " << t2BACKHP << std::endl;
            }
            hit=1;
            return 1;
        }

    }

    if(player == "t2"){
        if(t1FRONTHP>0 && bx>=t1X+t1SX-4  && bx<= t1X+t1SX+t1SX/5 +2 && by>= t1Y-(t1SX/5)-9 && by<= t1Y-(t1SX/5)-3+t1SY+(t1SX/5)+4){
            if(t1FRONTHP-5<=0){
                t1FRONTHP=0;
            }else{
                t1FRONTHP-=5;
            }
            hit=1;
            return 1;
        }

        if(t1BACKHP>0 && bx>=t1X-(t1SX/5)-2-t1SX/5 -6 && bx<=t1X-(t1SX/5)-2 && by>= t1Y-(t1SX/5)-9 && by<= t1Y-(t1SX/5)-3+t1SY+(t1SX/5)+4){
            if(t1BACKHP-5<=0){
                t1BACKHP=0;
            }else{
                t1BACKHP-=5;
            }
            hit=1;
            return 1;
        }

        if(t1TOPHP>0 && bx<= t1X+t1SX && bx>=t1X && by<=t1Y-(t1SX/5)-3+(t1SX/5) && by>=t1Y-(t1SX/5)-9){
            if(t1TOPHP-5<=0){
                t1TOPHP=0;
            }else{
                t1TOPHP-=5;
            }
            hit=1;
            return 1;
        }

        if(bx<= t1X+t1SX && bx>= t1X-6 && by>=t1Y-6 && by<= t1Y+t1SY){
            if(t1MHP-5<=0){
                t1MHP=0;
            }else{
                t1MHP-=5;
            }
            hit=1;
            return 1;
        }
    }

    return 0;
}

void Master::set_turn()
{
    turn=!turn;
}

void Master::set_deg(int DEG, std::string name)
{
    if(name == "deg1")
        t1DEG=DEG;
    if(name == "deg2")
        t2DEG=DEG;
}
