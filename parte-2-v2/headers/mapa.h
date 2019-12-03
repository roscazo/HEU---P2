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

        string getParada(){ return id; };
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

        string getName(){ return col; }
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

        void setEstado(int e){ estado = e; }

        string getColegio(){ return cole; }
        int getEstado(){ return estado; }

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
    void fill_graph();

    mapa() = default;

    string getInitial(){ return initial_pos; };
    int getCapacity(){ return capacity; };
    vector<colegio> getColegios(){ return colegios; };
    vector<vector<int>> getConexiones(){ return conexiones; };
    vector<child> getChildren(){ return children; };
    // ~mapa();
};

// parada::~parada()
// {
// };

// mapa::~mapa()
// {
// }
