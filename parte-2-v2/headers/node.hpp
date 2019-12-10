#include "state.hpp"

using namespace std;

class node
{
private:
    //vector<node> padre;
    vector<string> antecesores;
    //string previous = "";
    state estado;
    int g;
    int h;

    int heuristica();
    // void subir();
    // void bajar();
    // void mover();

public:
    node(state es, int coste, vector<string> antecesores);
    // {
    //     padre = _padre;
    //     estado = es;
    //     g = coste;
    //     h = heuristica();
    // };

    node();

    void set_state(state estado);
    void set_c(int coste);
    void set_h(int heu){ h = heu; };
    //void setPadre(node _padre){ padre.push_back(_padre); };
    void set_padre(string padre);
    //void setPrevious(string p){ previous += p; };

    int get_f();
    int get_c();
    state get_state();
    //node getPadre(){ return padre.back(); };
    string get_padre();
    vector<string> get_antecesores();
    //string getPrevious(){ return previous; };

    ~node();
};