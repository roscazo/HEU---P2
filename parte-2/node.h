#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stdexcept>
#include <fstream>

using namespace std;

class state
{
private:
    char parada;
    char colegio;
    vector<int> ninos;

public:
    state(/* args */);
    ~state();
};

state::state(/* args */)
{
}


class node
{
private:
    // state state;
    int coste;
    int heu;

    void sucesores();

public:
    node(/* args */);
    ~node();
};

node::node(/* args */)
{
}
