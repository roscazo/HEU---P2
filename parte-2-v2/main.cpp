#include "headers/node.hpp"

node initial_node;
// node final_node;

vector<colegio> colegios;
vector<vector<int>> conexiones;
int capacidad;

vector<node> open;
vector<node> closed;

bool sort_function(node i, node j)
{
    return (i.get_f() > j.get_f());
}

bool done(node n)
{
    state new_s = n.get_state();

    bool check = false;

    //if(new_s.get_parada() == "P1")
    //{
        for(size_t i = 0; i < new_s.get_children().size(); ++i)
        {
            if(new_s.get_children()[i].get_estado() == 2)
                check = true;
            else 
                return false;
        }
    //}
    //else return false;
    return check;
}

bool check_open(state &new_s)
{
    bool check = false;

    for (vector<node>::iterator it = open.begin(); it != open.end(); ++it)
    {
        if(check == true) return true;
        
        state aux_s = (*it).get_state();

        if(new_s.get_parada() == aux_s.get_parada())
        {
            for(size_t i = 0; i < new_s.get_children().size(); ++i)
            {
                if(new_s.get_children()[i].get_estado() == aux_s.get_children()[i].get_estado())
                    check = true;
                else 
                    return false;
            }
        }
        else check = false;
    }
    return check;
}

bool check_closed(state &new_s)
{
    bool check = false;

    for (vector<node>::iterator it = closed.begin(); it != closed.end(); ++it)
    {
        if(check == true) return true;
        
        state aux_s = (*it).get_state();

        if(new_s.get_parada() == aux_s.get_parada())
        {
            for(size_t i = 0; i < new_s.get_children().size(); ++i)
            {
                if(new_s.get_children()[i].get_estado() == aux_s.get_children()[i].get_estado())
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

        if( (*it).get_parada() == p )
            parada = (*it).get_cole();
        else parada = " ";
    }

    return parada;
}

void subir(node &_padre)
{
    state s = _padre.get_state();
    vector<string> aux_ant = _padre.get_antecesores();

    int control = 0;

    vector<child> aux_c = s.get_children();
    string aux_p = s.get_parada();
    int libre = s.get_seats();

    for (vector<child>::iterator it = aux_c.begin(); it != aux_c.end(); ++it)
    {
        string previous = " S: ";
        if( ((*it).get_parada() == aux_p) && ((*it).get_estado() == 0) && (libre > 0))
        {
            (*it).set_estado(1);
            libre -= 1;

            state new_s(aux_p, aux_c, libre);
            previous += (*it).get_colegio();
            previous += " ";

            if(control > 0) open.pop_back();

            if(!check_closed(new_s) && !check_open(new_s))
            {
                node new_n(new_s, _padre.get_c(), aux_ant);
                //padre.setPrevious(previous);
                ++control;
                open.push_back(new_n);
            }
        }    
    }
}

void bajar(node &_padre)
{
    state s = _padre.get_state();
    vector<string> aux_ant = _padre.get_antecesores();

    int control = 0;

    vector<child> aux_c = s.get_children();
    string aux_p = s.get_parada();
    int libre = s.get_seats();

    for (vector<child>::iterator it = aux_c.begin(); it != aux_c.end(); ++it)
    {
        string previous = " B: ";
        if( (((*it).get_estado() == 1) && ((*it).get_colegio() == check_colegio(aux_p)) ))
        {
            ++control;

            (*it).set_estado(2);
            libre += 1;

            state new_s(aux_p, aux_c, libre);
            previous += (*it).get_colegio();
            previous += " ";

            if(control > 0) open.pop_back();

            if(!check_closed(new_s) && !check_open(new_s))
            {
                node new_n(new_s, _padre.get_c(), aux_ant);
                //padre.setPrevious(previous);
                ++control;
                open.push_back(new_n);
            }
        }    
    }
}

void mover(node &_padre)
{
    state aux_s = _padre.get_state();
    vector<string> aux_ant = _padre.get_antecesores();

    int pos = aux_s.get_parada()[1] - 49;
    int i = 0;

    for (vector<int>::iterator it = conexiones[pos].begin(); it != conexiones[pos].end(); ++it)
    {
        ++i;
        if(*it == 1000) continue;
        else
        {
            char word = i+48;
            string p = "P";
            int cost = (*it) + _padre.get_c();
            state new_s((p+word), aux_s.get_children(), aux_s.get_seats());

            if(!check_closed(new_s) && !check_open(new_s))
            {
                node new_n(new_s, cost, aux_ant);
                new_n.set_padre(aux_s.get_parada());
                //new_n.setPrevious(aux_s.getParada());
                open.push_back(new_n);
            }
        }
    }
}

void sucesores(node &padre)
{
    mover(padre);
    subir(padre);
    bajar(padre);
}

void a_star(node initial_node)
{
    int j = 0;

    open.push_back(initial_node);

    cout << "\n-----ITERATIONS-----" << endl;
    //for(int i = 0; i < 10; ++i)
    while (!done(open.back()))
    {
        node parent = open.back();
        
        open.pop_back();

        sucesores(parent);
        closed.push_back(parent);

        sort(open.begin(), open.end(), sort_function);

        ++j;

        
        cout << j << endl;
    }
    
    // cout << "\n-----OPEN-----" << endl;
    // for (vector<node>::iterator it = open.begin(); it != open.end(); ++it)
    // {
    //     state e = (*it).get_state();
    //     //node p = (*it).getPadre();
    //     cout << "NODO " << e.get_parada() << endl;
    //     //cout << "PADRE " << p.getState().getParada() << endl;
    //     cout << "G " << (*it).get_c() << endl;
    //     cout << "COSTE " << (*it).get_f() << endl;
    //     cout << "NOÑOH ";

    //     for (vector<child>::iterator ch = e.get_children().begin(); ch != e.get_children().end(); ++ch)
    //     {
    //         cout << (*ch).get_estado() << " ";
    //     }
    //     cout << "\n" << endl;

    // }

    // cout << "\n-----CLOSED-----" << endl;
    // for (vector<node>::iterator it = closed.begin(); it != closed.end(); ++it)
    // {
    //     state e = (*it).get_state();
    //     //node p = (*it).getPadre();
    //     cout << "NODO " << e.get_parada() << endl;
    //     //cout << "PADRE " << p.getState().getParada() << endl;
    //     cout << "G " << (*it).get_c() << endl;
    //     cout << "COSTE " << (*it).get_f() << endl;
    //     cout << "NOÑOH ";

    //     for (vector<child>::iterator ch = e.get_children().begin(); ch != e.get_children().end(); ++ch)
    //     {
    //         cout << (*ch).get_estado() << " ";
    //     }
    //     cout << "\n" << endl;

    // }

    

    cout << "\nNODO " << open.back().get_state().get_parada() << endl;
    // // //state papa_state = papa->getState();
    cout << "PADRE " << open.back().get_padre()  << endl;
    cout << "COSTE " << open.back().get_c() << endl;
    cout << "PADRE ";
    for (vector<string>::iterator ch = open.back().get_antecesores().begin(); ch != open.back().get_antecesores().end(); ++ch)
    {
        cout << (*ch) << " ";
    }
    cout << endl;
}

int main()
{
    mapa map;
    state initial_state(map.get_initial(), map.get_children(), map.get_capacity());

    initial_node.set_state(initial_state);
    string paco = "END";
    initial_node.set_padre(paco);

    colegios = map.get_colegios();
    conexiones = map.get_conexiones();
    capacidad = map.get_capacity();

    a_star(initial_node);

    // bool i = false;
    // node papa = open.back();
    // cout << "\nNODO " << papa.getState().getParada() << endl;
    // cout << "COSTE " << papa.getCost() << endl;
    // cout << "NOÑOH ";
    // for (vector<child>::iterator ch = papa.getState().getChildren().begin(); ch != papa.getState().getChildren().end(); ++ch)
    // {
    //     cout << (*ch).getEstado() << " ";
    // }
    // cout << "\n" << endl;

//     string aux = papa.get_state().get_parada();
//     cout << aux;
//     while(!i)
//     {
//         cout << " <- " << papa.get_padre();
//         if(aux == papa.get_padre())
//             i = true;
//         else
//         {
//             cout << "-";
//             //papa = papa.get_padre();
//         }
//     }
//     cout << endl;
  }