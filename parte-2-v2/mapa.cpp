
#include "headers/mapa.h"

// vector<colegio> colegios;
// vector<vector<int>> conexiones;
// vector<child> children;

// string initial;
// int capacity;

void mapa::print_coso()
{
    cout << "------------- PARADAS -------------" << endl;
    // cout << "SIZE : " << conexiones.size() << endl;
    for(int i = 0; i < conexiones.size(); i++)
    {
        cout << "P" << i+1 << endl;
        for(int j = 0; j < conexiones[i].size(); j++)
        {
            cout << "Conectado con P" << j+1 << " en " << conexiones[i][j] << endl;
        }
    }

    cout << "\n------------- COLEGIOS -------------" << endl;
    for(int i = 0; i < colegios.size(); i++)
    {
        cout << "Colegio " << colegios[i].getName() << " en " << colegios[i].getParada() << endl;
    }

    cout << "\n------------- NIÑOS -------------" << endl;
    for(int i = 0; i < children.size(); i++)
    {
        cout << "Niño " << i << " en " << children[i].getParada() << " hacia "
        << children[i].getColegio() << endl;
    }

    cout << "\nPARADA INICIAL: " << initial_pos << endl;
    cout << "\nCAPACIDAD: " << capacity << endl;
}

int mapa::num_paradas(string str)
{
    int esp = 0;
    for (auto x : str) 
    {
        if(x == ' ' && esp != 0) ++esp;
        else if(x != ' ' && esp == 0) ++esp;
        else continue;
    }
    // esp -= 2;
    return esp;
}

void mapa::matrix_conexiones(string str, int size)
{
    string word = "";
    int i = -1;
    vector<int> row;

    row.reserve(size);

    for (auto x : str) 
    { 
        // cout << x << endl;
        if (x == ' ')
        { 
            // ID de la parada
            if(i == -1){ i = 0; word = ""; continue; } 
            // Celda con --
            else if(word == "--") row.push_back(1000);
            // Celda con número
            else row.push_back(stoi(word));

            ++i;
            word = "";
        } 
        else word = word + x;
        // cout << word << endl;
    }
    if(word == "--") row.push_back(1000);
    else row.push_back(stoi(word));

    conexiones.push_back(row);
}

void mapa::line_cole(string str)
{
    string word = "";
    string cole, par;

    for (auto x : str) 
    {
        if(x == ':') cole = word;

        else if(x == ' ') word = "";

        else if(x == ';')
        {
            par = word;
            colegio aux(par, cole);
            colegios.push_back(aux);
        }
        else word = word + x; 
    }
    par = word;
    colegio aux(par, cole);
    colegios.push_back(aux);
}

void mapa::line_children(string str)
{
    string word = "";
    string p, c;
    int num_ninos, esp = 0;

    for (auto x : str)
    {
        if(x == ':')
        {
            p = word;
            esp = 0;
        } 
        else if(x == ' ')
        {
            if(esp != 0) num_ninos = (int)word[0] - 48;

            else ++esp;

            word = "";
        } 
        else if(x == ',' || x == ';')
        {
            c = word;
            for(int i = 0; i < num_ninos; ++i)
            {
                child aux(p, c);
                children.push_back(aux);
            }
            esp = 0;
        }
        else word = word + x;
    }
    c = word;
    for(int i = 0; i < num_ninos; ++i)
    {
        child aux(p, c);
        children.push_back(aux);
    }
}

void mapa::line_capacity(string str)
{
    string word = "";
    int esp = 0;

    for (auto x : str)
    {
        if(x == ' ')
        {
            if(esp != 0)
            {
                initial_pos = word;
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
    capacity = (int)word[0] - 48;
}

void mapa::fill_graph()
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
    
    conexiones.reserve(num_p);

    // Recorre el fichero línea por línea
    while(getline(problema, str))
    {
        if(control == num_p)
            line_cole(str);
        else if(control == num_p + 1)
            line_children(str);
        else if(control == num_p +2)
            line_capacity(str);
        else
            matrix_conexiones(str, num_p);
        ++control;
    } 
    
    problema.close();

    print_coso();
}