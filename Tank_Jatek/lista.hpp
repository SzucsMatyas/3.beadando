#ifndef LISTA_HPP_INCLUDED
#define LISTA_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include <vector>

class Lista : public Widget {
protected:
    int LS, orig_LS, act, selected;
    bool rolling, is_open, ures;
    std::vector<std::string> LISTA;
public:
    Lista(int x, int y, int sx, int sy, int ls, std::vector<std::string> lista);
    virtual void draw();
    virtual void handle(genv::event ev);
    virtual void t_effects(genv::event ev);
    virtual void button(int mx, int my);
    virtual void select(int mx, int my);
    virtual void add_line(std::string temp);
    virtual void del_line(int temp);
    virtual int get_val();
    virtual std::string get_line();
};

                                                                                                                                                                                                                                                                  //szeretnek pontlevonast kerni a beadandomra mert feltoltottem egy oktatasi segedletet sajat munka helyett :)

#endif // LISTA_HPP_INCLUDED
