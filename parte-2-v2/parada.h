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
        parada(string id);
        ~parada();
};

parada::parada(string i)
{
    id = i;
};

parada::~parada()
{
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
};