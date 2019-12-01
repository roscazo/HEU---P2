#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "mapa.h"

using namespace std;

class node
{
private:
    // node parent;
    string pos;
    int g;
    int h;

public:
    node(string p, int coste);
    node() = default;

    void setPos(string p){ pos = p; };
    void setCost(int c){ g = c; };
    void setHeu(int heu){ h = heu; };

    int getF();
    string getPos(){ return pos; };

    ~node();
};

node::node(string p, int coste)
{
    pos = p;
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
