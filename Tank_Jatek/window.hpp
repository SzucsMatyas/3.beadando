#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include "widget.hpp"
#include <vector>
#include <fstream>

class Window {
protected:
    std::vector<Widget*> widgets;
public:
    virtual void esemeny(std::string wut){}
    void event_loop(int XX, int YY, bool fs) ;
};


#endif // WINDOW_HPP_INCLUDED