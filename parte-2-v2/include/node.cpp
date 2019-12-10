#include "../headers/node.hpp"

node::node(state estado, int cost, vector<string> antecesores)
{
    this->estado = estado;
    this->g = cost;
    this->antecesores = antecesores;
    this->h = heuristica();
}

node::node()
{
    this->g = 0;
    this->h = heuristica();
}

int node::heuristica()
{
    int heu = 12*(this->estado.get_children().size());
    int sum = 0;

    for (vector<child>::iterator ch = this->estado.get_children().begin(); ch != this->estado.get_children().end(); ++ch)
        sum += (*ch).get_estado()*6;

    // if(sum < heu)
    //     heu -= sum;
    heu = heu - sum;

    return heu;
}

void node::set_state(state estado)
{
    this->estado = estado;
}

void node::set_c(int cost)
{
    this->g = cost;
}

void node::set_padre(string parent)
{
    antecesores.push_back(parent);
}

int node::get_f()
{
    int func = this->g + this->h;
    return func;
}

int node::get_c()
{
    return this->g;
}

state node::get_state()
{
    return this->estado;
}

string node::get_padre()
{
    return antecesores.back();
}

vector<string> node::get_antecesores()
{
    return antecesores;
}

node::~node()
{
}