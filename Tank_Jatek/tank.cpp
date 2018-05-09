#include "tank.hpp"
#include "graphics.hpp"
#include <cmath>
#include <iostream>
#include <vector>

using namespace genv;
using namespace std;

const double PI  =3.141592653589793238463;

Tank::Tank(int x, int y, int sx, int sy, double mhp, double shp, int _r, int _g, int _b, char _oldal)
    : Widget(x,y,sx,sy)
{
    oldal=_oldal;
    deg=0;
    main_hp = mhp;
    top_hp = shp;
    back_hp = front_hp = shp*1.5;
    r=_r;
    g=_g;
    b=_b;
    shp_part = shp/255;
    mhp_part = mhp;
}

void Tank::handle(event ev)
{
    if(ev.keycode== -key_up && main_hp+1 <=mhp_part)
        main_hp++;
    if(ev.keycode== -key_down && main_hp-1 >=0)
        main_hp--;
    if(ev.keycode== -key_right){
        if(top_hp+1 <=shp_part*255)
            top_hp++;
        if(top_hp+1 >shp_part*255)
            top_hp=shp_part*255;
    }
    if(ev.keycode== -key_left){
        if(top_hp-1 >=0)
            top_hp--;
        if(top_hp-1 <0)
            top_hp=0;
    }
    if(ev.keycode== -key_pgup && back_hp+1 <=shp_part*255*1.5){
        back_hp++;
        front_hp++;
    }
    if(ev.keycode== -key_pgdn){
        if(back_hp-1 >=0){
            back_hp--;
            front_hp--;
        }
        if(back_hp-1 < 0){
            back_hp=0;
            front_hp=0;
        }
    }

    if(ev.button== btn_wheelup && deg+1<=135)
        deg+=1;
    if(ev.button== btn_wheeldown && deg-1>=0)
        deg-=1;
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
        gout << move_to(_X-(_SX/5), _Y-(_SX/5)-1) << color(255-(back_hp/(shp_part*1.5)),back_hp/(shp_part*1.5),0) << box((_SX/5)-4,_SY+(_SX/5)); //back shield
    }

    if(front_hp>0){
        gout << move_to(_X+_SX+2, _Y-(_SX/5)-3) << color(0,0,0) << box(_SX/5,_SY+(_SX/5)+4); //front shield
        gout << move_to(_X+_SX+4, _Y-(_SX/5)-1) << color(255-(front_hp/(shp_part*1.5)),front_hp/(shp_part*1.5),0) << box((_SX/5)-4,_SY+(_SX/5)); //front shield
    }

    if(top_hp>0){
        gout << move_to(_X, _Y-(_SX/5)-3) << color(0,0,0) << box(_SX,(_SX/5)); //top shield
        gout << move_to(_X+2, _Y-(_SX/5)-1) << color(255-(top_hp/shp_part),top_hp/shp_part,0) << box(_SX-4,(_SX/5)-4); //top shield
    }

    gout << move_to(_X-(_SX/5), _Y-(_SX/5)-24) << color(0,0,0) << box(_SX+(_SX/5)*2,10); //main_hp health bar
    gout << move_to(_X-(_SX/5)+1, _Y-(_SX/5)-23) << color(204,0,0) << box(_SX+(_SX/5)*2-2,8); //main_hp health bar missing health part
    if(main_hp >0)
        gout << move_to(_X-(_SX/5)+1, _Y-(_SX/5)-23) << color(0,153,0) << box(main_hp*((_SX+(_SX/5)*2-2)/mhp_part),8); //main_hp health bar green part

    if(oldal=='l')
        gout << move_to(_X+_SX/2, _Y+_SY/5) << color(0,0,0) << line_to((_X+_SX/2)+(cos(deg*(PI/180))*_SX),(_Y+_SY/5)-(sin(deg*(PI/180)))*_SX); //barrel
    if(oldal=='r')
        gout << move_to(_X+_SX/2, _Y+_SY/5) << color(0,0,0) << line_to((_X+_SX/2)-(cos(deg*(PI/180))*_SX),(_Y+_SY/5)-(sin(deg*(PI/180)))*_SX); //barrel
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

void Tank::t_effects(Master mester)
{
    double msx((_X+_SX/2)+(cos(deg*(PI/180))*_SX)), msy((_Y+_SY/5)-(sin(deg*(PI/180)))*_SX), vx(cos(deg*(PI/180))*6), vy(-sin(deg*(PI/180))*6), gravity(0.03);
//    int X2(x2), Y2(y2), SX2(sx2), SY2(sy2);
//    double TOP2(top2), FRONT2(front2), BACK2(back2);
    event ev;
    gin.timer(5);
    while(gin >> ev && !mester.hitdet(msx, msy)) {
//        if(ev.type == ev_timer){
////            cout << "ok" << endl;
//            if(msx>0 && msx<XX-6 && msy>0 && msy < YY-6){
//                gout << move_to(msx,msy) << color(0,0,0) << box(6,6) << refresh;
//                gout << move_to(msx,msy) << color(255,255,255) << box(6,6);
//            }
//            if(msx>0 && msx<XX-6 && msy<0){
//                gout << move_to(msx,0) << color(0,0,255) << box(6,6) << refresh;
//                gout << move_to(msx,0) << color(255,255,255) << box(6,6);
//            }
//            draw();
//            vy += gravity;
//            msx += vx;
//            msy += vy;
//        }
    }
}

//int Tank::get_X(){return _X;}
//int Tank::get_Y(){return _Y;}
//int Tank::get_SX(){return _SX;}
//int Tank::get_SY(){return _SY;}
//double Tank::get_top(){return top_hp;}
//double Tank::get_front(){return front_hp;}
//double Tank::get_back(){return back_hp;}
