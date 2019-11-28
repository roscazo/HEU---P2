#include <iostream>
#include <string>
#include <vector>

using namespace std;

class parada
{
private:
    string id;
    string colegio;
    
public:
    //parada(char id, int num);
    parada();
    ~parada();

    vector<int> conexiones;
    vector<string> n_parada;

    void setID(string c){ id = c; cout << "HECHO " << id << endl;}
    string getID(){ return id; }

    void setColegio(string c){ colegio = c; cout << "TONTO" << endl;}
    string getColegio(){ return colegio; }
};

parada::parada()
{
}

parada::~parada()
{
}
