#include "tank.hpp"
#include "graphics.hpp"
#include <cmath>
#include <vector>

using namespace genv;
using namespace std;

const double PI  =3.141592653589793238463;

Tank::Tank(int x, int y, int sx, int sy, double mhp, double shp, int _r, int _g, int _b, char _oldal)
    : Widget(x,y,sx,sy)
{
    focus=0;
    focusable=0;
    oldal=_oldal;
    deg=20;
    main_hp = mhp;
    top_hp = shp;
    back_hp = front_hp = shp*2;
    r=_r;
    g=_g;
    b=_b;
    shp_part = shp/255;
    mhp_part = mhp;
}

void Tank::reset(double mhp, double shp)
{
    main_hp = mhp;
    top_hp = shp;
    back_hp = front_hp = shp*2;
    deg=20;
}

void Tank::draw()
{
    gout << move_to(_X, _Y) << color(0,0,0) << box(_SX,_SY); //main part
    gout << move_to(_X+3, _Y+3) << color(r,g,b) << box(_SX-6,_SY-6); //main part
    gout << move_to(_X-1, _Y+_SY/2) << color(0,0,0) << box(_SX+2,_SY/2+1); // track
    gout << move_to(_X+1, _Y+_SY/2+2) << color(64,64,64) << box(_SY/2-3,_SY/2-3); // gear left
    gout << move_to(_X+_SX/2-_SY/4+2, _Y+_SY/2+2) << color(64,64,64) << box(_SY/2-3,_SY/2-3); // gear mid
    gout << move_to(_X+_SX-_SY/2 +2, _Y+_SY/2+2) << color(64,64,64) << box(_SY/2-3,_SY/2-3); // gear right

    if(back_hp>0){
        gout << move_to(_X-(_SX/5)-2, _Y-(_SX/5)-3) << color(0,0,0) << box(_SX/5,_SY+(_SX/5)+4); //back shield
        gout << move_to(_X-(_SX/5), _Y-(_SX/5)-1) << color(255-(back_hp/(shp_part*2)),back_hp/(shp_part*2),0) << box((_SX/5)-4,_SY+(_SX/5)); //back shield
    }

    if(front_hp>0){
        gout << move_to(_X+_SX+2, _Y-(_SX/5)-3) << color(0,0,0) << box(_SX/5,_SY+(_SX/5)+4); //front shield
        gout << move_to(_X+_SX+4, _Y-(_SX/5)-1) << color(255-(front_hp/(shp_part*2)),front_hp/(shp_part*2),0) << box((_SX/5)-4,_SY+(_SX/5)); //front shield
    }

    if(top_hp>0){
        gout << move_to(_X, _Y-(_SX/5)-3) << color(0,0,0) << box(_SX,(_SX/5)); //top shield
        gout << move_to(_X+2, _Y-(_SX/5)-1) << color(255-(top_hp/shp_part),top_hp/shp_part,0) << box(_SX-4,(_SX/5)-4); //top shield
    }

    gout << move_to(_X-(_SX/5), _Y-(_SX/5)-24) << color(0,0,0) << box(_SX+(_SX/5)*2,10); //main_hp health bar
    gout << move_to(_X-(_SX/5)+1, _Y-(_SX/5)-23) << color(204,0,0) << box(_SX+(_SX/5)*2-2,8); //main_hp health bar missing health part
    if(main_hp >0)
        gout << move_to(_X-(_SX/5)+1, _Y-(_SX/5)-23) << color(0,153,0) << box(main_hp*((_SX+(_SX/5)*2-2)/mhp_part),8); //main_hp health bar green part

    if(oldal=='l'){
        for(int i=-2; i<=2;i++){
            for(int j=-2; j<=2;j++){
                gout << move_to(_X+_SX/2 +i, _Y+_SY/5 +j) << color(32,32,32) << line_to((_X+_SX/2)+(cos(deg*(PI/180))*_SX) +i,(_Y+_SY/5)-(sin(deg*(PI/180)))*_SX +j); //barrel
            }
        }
    }
    if(oldal=='r'){
        for(int i=-2; i<=2;i++){
            for(int j=-2; j<=2;j++){
                gout << move_to(_X+_SX/2 +i, _Y+_SY/5 +j) << color(32,32,32) << line_to((_X+_SX/2)-(cos(deg*(PI/180))*_SX) +i,(_Y+_SY/5)-(sin(deg*(PI/180)))*_SX +j); //barrel
            }
        }
    }
}
int Tank::get_val()
{
    return main_hp;
}

bool Tank::hit_det(double msx, double msy, int XX, int YY)
{
    if(msx<0 || msx>XX-6 || msy > YY-6){
        return 1;
    }else
        return 0;
}


void Tank::set_fronthp(double temp){front_hp=temp;}
void Tank::set_backhp(double temp){back_hp=temp;}
void Tank::set_tophp(double temp){top_hp=temp;}
void Tank::set_mainhp(double temp){main_hp=temp;}
