#include "node.h"

#include <sstream>

int main()
{
    int n;
    string aux;
    string line;

    ifstream myfile("problema.prob");
    vector<string> matrix;

    getline(myfile, line);
    istringstream is( line );
    while( is >> aux ) {
        //matrix.push_back( aux );
        n++;
    }
    cout << n << endl;
        while(getline(myfile, line))
        {
            istringstream is( line );
        while( is >> aux ) 
        {
            matrix.push_back(aux);
        }
        }
        
    //     getline(myfile, line) >> aux;
    //     // for (int j = 0; j < n; j++) 
    //     matrix.push_back(aux)

    for (int i = 0; i < n; i++) 
    {
        //for (int j = 0; i < n; i++) 
            cout << matrix[i];
        cout << endl;
    }

    // for (int i = 0; i < n; i++) 

    return 0;
}