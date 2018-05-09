#ifndef MASTER_HPP_INCLUDED
#define MASTER_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"

class Master {
private:
    std::vector<Widget*> widgets;
    int XX, YY;
public:
    Master(std::vector<Widget*> widgets, int XX, int YY);
    virtual bool hitdet(double msx, double msy);
//    int get_x();
//    int get_sx();
//    int get_y();
//    int get_sy();
};


#endif // MASTER_HPP_INCLUDED
