#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stdexcept>
#include <fstream>

#include "parada.h"

using namespace std;

class state : public parada
{
private:
    parada par;
    vector<int> ninos;
    int max_capacidad;

public:
    state();
    //~state();

    void setParada(parada p){ par = p; }
    void setCapacity(int num)
    { 
        max_capacidad = num; 
        ninos.reserve(max_capacidad);
    }
};

state::state()
{

}