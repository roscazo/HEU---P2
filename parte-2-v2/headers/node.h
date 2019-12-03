#include "state.h"

using namespace std;

class node
{
private:
    node* padre;
    state estado;
    int g;
    int h;

    // void subir();
    // void bajar();
    // void mover();

public:
    node(node* p, state es, int coste);
    node();

    void setState(state e){ estado = e; };
    void setCost(int c){ g = c; };
    void setHeu(int heu){ h = heu; };

    int getF();
    int getCost(){ return g; };
    state getState(){ return estado; };
    node getPadre(){ return *padre; };

    ~node();
};

node::node(node *p, state es, int coste)
{
    padre = p;
    estado = es;
    g = coste;
    h = 0;
}

node::node()
{
}

node::~node()
{
}

int node::getF()
{
    return (g + h);
}
