#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stdexcept>
#include <fstream>

#include "state.h"

using namespace std;

class node
{
public:
    node(node p, state s, int g, int h);
    node();
    ~node();

    void sucesores(vector<node> &open);
    int equal(node n);

    void setCost(int g);
    int getCost(){ return g; };

    void setHeu(int h);
    int getHeu(){ return h; };

private:
    //node node_parent;
    state s;

    int g;
    int h;

    
};
