
#include "parada.h"

vector<colegio> colegios;
vector<vector<int>> conexiones;
vector<child> children;

void print_coso()
{
    cout << "SIZE : " << conexiones.size() << endl;
    for(int i = 0; i < conexiones.size(); i++)
    {
        cout << "P" << i+1 << endl;
        for(int j = 0; j < conexiones[i].size(); j++)
        {
            cout << "Conectado con " << j+1 << " en " << conexiones[i][j] << endl;
        }
    }

}

int num_paradas(string str)
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

void matrix_conexiones(string str, int size)
{
    string word = "";
    int i = -1;
    vector<int> row;

    row.reserve(size);

    for (auto x : str) 
    { 
        cout << x << endl;
        if (x == ' ')
        { 
            // 1ª COL --> ID de la parada
            if(i == -1){ i = 0; word = ""; continue; } 
            // Celda con --
            else if(word == "--") row.push_back(1000);
            // Celda con número
            else row.push_back(stoi(word));

            ++i;
            word = "";
        } 
        else word = word + x;
        cout << word << endl;
    }
    if(word == "--") row.push_back(1000);
    else row.push_back(stoi(word));

    conexiones.push_back(row);
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
    
    conexiones.reserve(num_p);
    // Recorre el fichero línea por línea
    while(getline(problema, str))
    {
        // if(control == num_p)
        //     num_col = line_cole(str);
        // else if(control == num_p + 1)
        //     line_kids(str);
        // else if(control == num_p +2)
        //     line_capacity(str);
        // else
            matrix_conexiones(str, num_p);
        // ++control;
    } 
    
    problema.close();
}

int main()
{
    fill_graph();
    print_coso();
}