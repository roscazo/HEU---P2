#include "mapa.h"

class state
{
private:
    string position;
    vector<child> children;
    int available;

public:
    state(string p, vector<child> c, int a);
    ~state();

    void subir_pasajero(int i);
    void bajar_pasajero(int i);

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

void state::subir_pasajero(int i)
{
    available -= 1;
}

void state::bajar_pasajero(int i)
{
    available += 1;
}

state::~state()
{
}
