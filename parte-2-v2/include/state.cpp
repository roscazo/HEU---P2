#include "../headers/state.hpp"

state::state(string position, vector<child> children, int available)
{
    this->position = position;
    this->children = children;
    this->available_seats = available;
}

state::state()
{
}

void state::set_position(string position)
{ 
    this->position = position; 
}

void state::set_children(vector<child> children)
{ 
    this->children = children; 
}

string state::get_parada(){ return this->position; }

vector<child> state::get_children(){ return this->children; }

int state::get_seats(){ return this->available_seats; }

state::~state()
{
}