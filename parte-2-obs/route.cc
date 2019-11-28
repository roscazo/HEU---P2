#include <sstream>
#include <algorithm>

#include "node.h"
//#include "parada.h"

vector<parada> mapa;
state initial_state;

void print_coso()
{
    cout << mapa.size() << endl;
    for(int i = 0; i < mapa.size(); i++)
    {
        cout << "ID = " << mapa[i].getID() << endl;
        cout << "COLE = " << mapa[i].getColegio() << endl;

        for(int j = 0; j < mapa[i].conexiones.size(); j++)
        {
            cout << "Conectado con = " << j+1 << " en " << mapa[i].conexiones[j] << endl;
        }
        for(int j = 0; j < mapa[i].n_parada.size(); j++)
        {
            cout << "Niño " << j << " va a: " << mapa[i].n_parada[j] << endl;
        }
    }

}

int num_paradas(string str)
{
    int esp = 0;
    for (auto x : str) 
    {
        if(x == ' ') ++esp;
    }
    esp -= 2;
    return esp;
}

void matrix_conexiones(string str, int size)
{
    string word = "";
    int i = -1;
    parada aux;

    aux.conexiones.reserve(size);

    for (auto x : str) 
    { 
        if (x == ' ')
        { 
            // 1ª COL --> ID de la parada
            if(i == -1) aux.setID(word);
            // Celda con --
            else if(word == "--") aux.conexiones.push_back(100);
            // Celda con número
            else aux.conexiones.push_back(stoi(word));

            ++i;
            word = "";
        } 
        else word = word + x; 
    }
    if(word == "--") aux.conexiones.push_back(100);
    else aux.conexiones.push_back(stoi(word));

    mapa.push_back(aux);
    i = -1;
}

int line_cole(string str)
{
    string word = "";
    string colegio;
    int num_col = 0;

    for (auto x : str) 
    {
        if(x == ':')
        {
            colegio = word;
            ++num_col;
        } 
        else if(x == ' ')
        {
            word = "";
            continue;
        } 
        else if(x == ';')
        {
            // cout << "Número = " << ((int)word[1])-49 << endl;
            mapa[((int)word[1])-49].setColegio(colegio);
        }
        else word = word + x; 
        // cout << "word = " << word << endl;
    }
    mapa[((int)word[1])-49].setColegio(colegio);

    return num_col;
}

void line_kids(string str)
{
    string word = "";
    int p;
    int num_ninos, esp = 0;

    for (auto x : str)
    {
        if(x == ':')
        {
            p = (int)word[1] - 49;
            mapa[p].n_parada.reserve(10);
            cout << "Parada = " << p+1 << endl;
            esp = 0;
        } 
        else if(x == ' ')
        {
            if(esp != 0)
            {
                num_ninos = (int)word[0] - 48;
                cout << "Num_niños = " << num_ninos << endl;
                esp = 0;
                word = "";
            }
            else
            {
                word = "";
                ++esp;
            }
        } 
        else if(x == ',' || x == ';')
        {
            cout << "UFFF" << endl;
            for(int i = 0; i < num_ninos; ++i)
                mapa[p].n_parada.push_back(word);
            cout << "DONE" << endl;
        }
        else word = word + x; 

        cout << "word = " << word << endl;
    }
    for(int i = 0; i < num_ninos; ++i)
                mapa[p].n_parada.push_back(word);
}

void line_capacity(string str)
{
    string word = "";
    int esp = 0;
    int p;

    for (auto x : str)
    {
        if(x == ' ')
        {
            if(esp != 0)
            {
                p = (int)word[1] - 49;
                word = "";
            }
            else
            {
                word = "";
                ++esp;
            }
        }
        else word = word + x;
    }
    int cap = (int)word[0] - 48;
    initial_state.setParada(mapa[p]);
    initial_state.setCapacity(cap);
}

void fill_graph()
{
    ifstream problema;
    string str;
    
    int control = 0;
    int num_col;

    problema.open("problema.prob");
    if (!problema) 
    {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    // Busca el número de paradas
    getline(problema, str); 
    int num_p = num_paradas(str);
    cout << "Num_paradas: " << num_p << endl; 
    
    mapa.reserve(num_p);
    // Recorre el fichero línea por línea
    while(getline(problema, str))
    {
        if(control == num_p)
            num_col = line_cole(str);
        else if(control == num_p + 1)
            line_kids(str);
        else if(control == num_p +2)
            line_capacity(str);
        else
            matrix_conexiones(str, num_p);
        ++control;
    } 
    print_coso();
    
    problema.close();
}

void ordena()
{

}

void a_star()
{
    // vector<node>open;
    // vector<node>closed;
    // int exito;
    // node N, goal;

    // while(!open.empty() || !exito)
    // {
    //     N = open.back();
    //     open.pop_back();

    //     if(!N.equal(goal)) 
    //     {
    //         N.sucesores(open);
    //     //     for(int i = 0; i < closed.size(); i++)
    //     //     {
    //     //         if()
    //     //     }

    //     }

    //     else exito = 1;
        
    // }
}

int main()
{
    fill_graph();
    

    return 0;
}