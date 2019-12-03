#include "headers/node.h"

node initial_node;
node final_node;

vector<colegio> colegios;
vector<vector<int>> conexiones;
int capacidad;

vector<node> open;
vector<node> closed;
int done;

bool sort_function(node i, node j)
{
    return (i.getF() > j.getF());
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

void subir(node padre)
{
    state s = padre.getState();

    vector<child> aux_c = s.getChildren();
    string aux_p = s.getParada();
    int libre = s.getPassengers();

    for (vector<child>::iterator it = aux_c.begin(); it != aux_c.end(); ++it)
    {
        if( ((*it).getParada() == aux_p) && ((*it).getState() == 0) && (libre > 0))
        {
            (*it).setState(1);
            libre -= 1;
            state aux_s(aux_p, aux_c, libre);
            node aux_n(&padre, aux_s, padre.getCost());
            open.push_back(aux_n);
        }    
    }
}

void bajar(node padre)
{
    state s = padre.getState();

    vector<child> aux_c = s.getChildren();
    string aux_p = s.getParada();
    int libre = s.getPassengers();

    for (vector<child>::iterator it = children.begin(); it != children.end(); ++it)
    {
        if( ((*it).getParada() == aux_p) && ((*it).getState() == 1) && ((*it).getColegio() == check_colegio(aux_p)) )
        {
            (*it).setState(2);
            libre += 1;
            state aux_s(aux_p, aux_c, libre);
            node aux_n(&padre, aux_s, padre.getCost());
            open.push_back(aux_n);
        }    
    }
}

void mover(node padre)
{
    int aux_s = padre.getState();
    int pos = aux_s.getParada()[1] - 49;

    for (vector<int>::iterator it = conexiones[pos].begin(); it != conexiones[pos].end(); ++it)
    {
        if(*it == 1000) continue;
        else
        {
            char word = (*it)+49;
            string p = "P";
            int cost = (*it) + padre.getCost();

            state aux_s((p+word), aux_s.getChildren(), aux_s.getPassengers());
            node aux_n(&padre, aux_s, cost);
            open.push_back(aux_n);
        }
    }
}

void sucesores(node padre)
{
    mover(padre);
    subir(padre);
    bajar(padre);
}

void a_star()
{
    node parent;

    open.push_back(initial_node);
    done = 0;

    // for (size_t i = 0; i < 3; i++)
    // // while (!open.empty() || done == 0)
    // {
        parent = open.back();
        cout << "PATER " << parent.getState().getParada() << endl;
        open.pop_back();
        sucesores(parent);
        sort(open.begin(), open.end(), sort_function);
    //     for(int i = 0; i < closed.size(); ++i)
    //     {
    //         if(check == closed.at(i))
    //     }
    //     open.pop_back();
    // }
    
    // cout << "\nLA LIADITA" << endl;
    // for(int i = 0; i < open.size(); ++i){
    //     cout << "NODO " << open[i].getParada() << endl;
    //     cout << "COSTE " << open[i].getF() << "\n" << endl;
    // }
    
    
}

int main()
{
    mapa map;
    map.fill_graph();
    state initial_state(map.getInitial(), map.getChildren(), map.getCapacity());

    initial_node.setState(initial_state);
    initial_node.setCost(0);

    colegios = map.getColegios();
    conexiones = map.getConexiones();
    capacidad = map.getCapacity();

    a_star();
}