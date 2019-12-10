#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class parada
{
    private:
        string id;

    public:
        parada(string i){ id = i; };
        // ~parada();

        string get_parada(){ return id; };
};

class colegio : public parada
{
    private:
        string col;

    public:
        colegio(string p, string c) : parada(p)
        {
            col = c; 
        }

        string get_cole(){ return col; }
};

class child : public parada
{
    private:
        string cole;
        int estado;

    public:
        child(string p, string c) : parada(p)
        {
            cole = c;
            estado = 0;
        }

        void set_estado(int e){ estado = e; }

        string get_colegio(){ return cole; }
        int get_estado(){ return estado; }

};

class mapa
{
private:
    vector<colegio> colegios;
    vector<vector<int>> conexiones;
    vector<child> children;

    string initial_pos;
    int capacity;

    int num_paradas(string str);
    void matrix_conexiones(string str, int size);
    void line_cole(string str);
    void line_children(string str);
    void line_capacity(string str);
    void print_coso();

public:
    mapa();
    ~mapa();

    string get_initial(){ return initial_pos; };
    int get_capacity(){ return capacity; };
    vector<colegio> get_colegios(){ return colegios; };
    vector<vector<int>> get_conexiones(){ return conexiones; };
    vector<child> get_children(){ return children; };
    // 
};

// parada::~parada()
// {
// };

// mapa::~mapa()
// {
// }
