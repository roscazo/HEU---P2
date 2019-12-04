#include "headers/node.h"

node initial_node;
node final_node;

vector<colegio> colegios;
vector<vector<int>> conexiones;
int capacidad;

vector<node> open;
vector<node> closed;

bool sort_function(node i, node j)
{
    return (i.getF() > j.getF());
}

bool done(node n)
{
    state new_s = n.getState();

    bool check;

    if(new_s.getParada() == "P1")
    {
        for(size_t i = 0; i < new_s.getChildren().size(); ++i)
        {
            if(new_s.getChildren()[i].getEstado() == 2)
                check = true;
            else 
                return false;
        }
    }
    else return false;
    return check;
}

bool check_open(node n)
{
    state new_s = n.getState();
    bool check;

    for (vector<node>::iterator it = open.begin(); it != open.end(); ++it)
    {
        if(check == true) return true;
        
        state aux_s = (*it).getState();

        if(new_s.getParada() == aux_s.getParada())
        {
            for(size_t i = 0; i < new_s.getChildren().size(); ++i)
            {
                if(new_s.getChildren()[i].getEstado() == aux_s.getChildren()[i].getEstado())
                    check = true;
                else 
                    return false;
            }
        }
        else check = false;
    }
    return check;
}

bool check_closed(node n)
{
    state new_s = n.getState();
    bool check;

    for (vector<node>::iterator it = closed.begin(); it != closed.end(); ++it)
    {
        if(check == true) return true;
        
        state aux_s = (*it).getState();

        if(new_s.getParada() == aux_s.getParada())
        {
            for(size_t i = 0; i < new_s.getChildren().size(); ++i)
            {
                if(new_s.getChildren()[i].getEstado() == aux_s.getChildren()[i].getEstado())
                    check = true;
                else 
                    return false;
            }
        }
        else check = false;
    }
    return check;
}

string check_colegio(string p)
{
    string parada = " ";

    for (vector<colegio>::iterator it = colegios.begin(); it != colegios.end(); ++it)
    {
        if(parada != " ") return parada;

        if( (*it).getParada() == p )
            parada = (*it).getName();
        else parada = " ";
    }

    return parada;
}

void subir(node padre)
{
    state s = padre.getState();

    int control = 0;

    vector<child> aux_c = s.getChildren();
    string aux_p = s.getParada();
    int libre = s.getPassengers();

    for (vector<child>::iterator it = aux_c.begin(); it != aux_c.end(); ++it)
    {
        if( ((*it).getParada() == aux_p) && ((*it).getEstado() == 0) && (libre > 0))
        {
            (*it).setEstado(1);
            libre -= 1;

            state new_s(aux_p, aux_c, libre);
            node new_n(&padre, new_s, padre.getCost());

            if(control > 0) open.pop_back();

            if(!check_closed(new_n) && !check_open(new_n))
            {
                ++control;
                open.push_back(new_n);
            }
        }    
    }
}

void bajar(node padre)
{
    state s = padre.getState();

    int control = 0;

    vector<child> aux_c = s.getChildren();
    string aux_p = s.getParada();
    int libre = s.getPassengers();

    for (vector<child>::iterator it = aux_c.begin(); it != aux_c.end(); ++it)
    {
        if( (((*it).getEstado() == 1) && ((*it).getColegio() == check_colegio(aux_p)) ))
        {
            ++control;

            (*it).setEstado(2);
            libre += 1;

            state new_s(aux_p, aux_c, libre);
            node new_n(&padre, new_s, padre.getCost());

            if(control > 0) open.pop_back();

            if(!check_closed(new_n) && !check_open(new_n))
            {
                ++control;
                open.push_back(new_n);
            }
        }    
    }
}

void mover(node padre)
{
    state aux_s = padre.getState();
    int pos = aux_s.getParada()[1] - 49;
    int i = 0;

    for (vector<int>::iterator it = conexiones[pos].begin(); it != conexiones[pos].end(); ++it)
    {
        ++i;
        if(*it == 1000) continue;
        else
        {
            char word = i+48;
            string p = "P";
            int cost = (*it) + padre.getCost();
            state new_s((p+word), aux_s.getChildren(), aux_s.getPassengers());
            node new_n(&padre, new_s, cost);

            if(!check_closed(new_n) && !check_open(new_n))
                open.push_back(new_n);
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
    int j = 0;
    node parent;

    open.push_back(initial_node);

    for(int i = 0; i < 50; ++i)
    //while (!done(open.back()))
    {
        parent = open.back();
        //cout << "PATER " << parent.getState().getParada() << endl;
        open.pop_back();
        //cout << "CHECK " << check_closed(parent) << endl;
        // if(!check_closed(parent))
        // {
        //     sucesores(parent);
        //     closed.push_back(parent);   
        // }
        sucesores(parent);
        closed.push_back(parent);
        sort(open.begin(), open.end(), sort_function);
        ++j;
    }
    
    cout << "\n-----OPEN-----" << endl;
    for (vector<node>::iterator it = open.begin(); it != open.end(); ++it)
    {
        state e = (*it).getState();
        //node p = (*it).getPadre();
        cout << "NODO " << e.getParada() << endl;
        //cout << "PADRE " << p.getState().getParada() << endl;
        cout << "G " << (*it).getCost() << endl;
        cout << "COSTE " << (*it).getF() << endl;
        cout << "NOÑOH ";

        for (vector<child>::iterator ch = e.getChildren().begin(); ch != e.getChildren().end(); ++ch)
        {
            cout << (*ch).getEstado() << " ";
        }
        cout << "\n" << endl;

    }

    cout << "\n-----CLOSED-----" << endl;
    for (vector<node>::iterator it = closed.begin(); it != closed.end(); ++it)
    {
        state e = (*it).getState();
        //node p = (*it).getPadre();
        cout << "NODO " << e.getParada() << endl;
        //cout << "PADRE " << p.getState().getParada() << endl;
        cout << "G " << (*it).getCost() << endl;
        cout << "COSTE " << (*it).getF() << endl;
        cout << "NOÑOH ";

        for (vector<child>::iterator ch = e.getChildren().begin(); ch != e.getChildren().end(); ++ch)
        {
            cout << (*ch).getEstado() << " ";
        }
        cout << "\n" << endl;

    }
    
    cout << "\n-----ITERATIONS-----" << endl;
    cout << j << endl;
    
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