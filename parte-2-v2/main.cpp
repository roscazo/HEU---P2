#include "headers/node.h"

node initial_node;
node final_node;

vector<colegio> colegios;
vector<vector<int>> conexiones;

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
        //cout << "POS " << conexiones[pos][i] << endl;
        if(conexiones[pos][i] == 1000) continue;
        else
        {
            char word = i+49;
            string p = "P";

            // node aux((p+word), conexiones[pos][i]);
            // open.push_back(aux);
        }
    }
}

string check_colegio(string p)
{
    for (vector<colegio>::iterator it = colegios.begin(); it != colegios.end(); ++it)
    {
        if( (*it).getParada() == p )
            return (*it).getName();
    }

    return NULL;
}

void subir(node n)
{
    state p = n.getState();
    for (vector<child>::iterator it = p.getChildren().begin(); it != p.getChildren().end(); ++it)
    {
        if( ((*it).getParada() == p.getParada()) && ((*it).getEstado() == 0) && (p.getPassengers() > 0))
        {
            (*it).setEstado(1);
            p.subir_pasajero(1);
        }    
    }
}

void bajar(node n)
{
    string p = n.getPos();
    for (vector<child>::iterator it = children.begin(); it != children.end(); ++it)
    {
        if( ((*it).getParada() == p) && ((*it).getEstado() == 1) && ((*it).getColegio() == check_colegio(p)) )
        {
            (*it).setEstado(2);
        }    
    }
}

void a_star()
{
    node parent;

    open.push_back(initial_node);
    done = 0;

    for (size_t i = 0; i < 3; i++)
    // while (!open.empty() || done == 0)
    {
        parent = open.back();
        cout << "PATER " << parent.getPos() << endl;
        open.pop_back();
        sucesores(parent);
        sort(open.begin(), open.end(), sort_function);
    //     for(int i = 0; i < closed.size(); ++i)
    //     {
    //         if(check == closed.at(i))
    //     }
    //     open.pop_back();
    }
    
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
    state initial_state(map.getInitial(), map.getChildren(), map.getCapacity());

    initial_node.setEstado(initial_state);
    initial_node.setCost(0);

    colegios = map.getColegios();
    conexiones = map.getConexiones();

    a_star();
}