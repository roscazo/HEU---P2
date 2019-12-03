#include "state.h"

using namespace std;

class node
{
private:
    // node parent;
    state estado;
    int g;
    int h;

    // void subir();
    // void bajar();
    // void mover();

public:
    node(state es, int coste);
    node() = default;

    void setEstado(state e){ estado = e; };
    void setCost(int c){ g = c; };
    void setHeu(int heu){ h = heu; };

    int getF();
    state getState(){ return estado; };

    ~node();
};

node::node(state es, int coste)
{
    estado = es;
    g = coste;
    h = 0;
}

node::~node()
{
}

int node::getF()
{
    return (g + h);
}
