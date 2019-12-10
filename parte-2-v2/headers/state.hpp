#include "mapa.hpp"

class state
{
private:
    string position;
    vector<child> children;
    int available_seats;

public:
    state(string p, vector<child> c, int a);
    state();
    ~state();

    void set_position(string p);
    void set_children(vector<child> c);

    string get_parada();
    vector<child> get_children();
    int get_seats();
};






