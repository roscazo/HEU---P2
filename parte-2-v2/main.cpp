#include "headers/node.h"

node initial_node;
node final_node;

vector<colegio> colegios;
vector<vector<int>> conexiones;
vector<child> children;

vector<node> open;
vector<node> closed;
int done;

bool sort_function(node i, node j)
{
    return (i.getF() > j.getF());
}

void sucesores(node padre)
{
    int pos = padre.getPos()[1] - 49;

    for(int i = 0; i < conexiones[pos].size(); ++i)
    {
        cout << "POS " << conexiones[pos][i] << endl;
        if(conexiones[pos][i] == 1000) continue;
        else
        {
            char word = i+49;
            string p = "P";

            node aux((p+word), conexiones[pos][i]);
            open.push_back(aux);
        }
    }
    sort(open.begin(), open.end(), sort_function);
    open.pop_back();
}

void a_star()
{
    node check;

    open.push_back(initial_node);
    done = 0;

    sucesores(initial_node);

    // while (!open.empty() || done == 1)
    // {
    //     check = open.back();
    //     for(int i = 0; i < closed.size(); ++i)
    //     {
    //         if(check == closed.at(i))
    //     }
    //     open.pop_back();
    // }
    
    cout << "\nLA LIADITA" << endl;
    for(int i = 0; i < open.size(); ++i){
        cout << "NODO " << open[i].getPos() << endl;
        cout << "COSTE " << open[i].getF() << "\n" << endl;
    }
    
    
}

int main()
{
    mapa map;
    map.fill_graph();

    initial_node.setPos(map.getInitial());
    initial_node.setCost(0);

    colegios = map.getColegios();
    conexiones = map.getConexiones();
    children = map.getChildren();

    a_star();
}