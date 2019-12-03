#include "mapa.h"

class state
{
private:
    string position;
    vector<child> children;
    int available;

public:
    state(string p, vector<child> c, int a);
    state();
    ~state();

    void setPosition(string p){ position = p; };
    void setChildren(vector<child> c){ children = c; };

    string getParada(){ return position; };
    vector<child> getChildren(){ return children; };
    int getPassengers(){ return available; };
};

state::state(string p, vector<child> c, int a)
{
    position = p;
    children = c;
    available = a;
}

state::state()
{
}

state::~state()
{
}
