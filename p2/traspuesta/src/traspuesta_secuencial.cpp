#include <cstdlib>
#include <iostream>
#include <chrono>
#include <cmath>

#include "matriz.h"


using namespace std;

//#define MEDICION

int main(int argc, char** argv) {
    
    int n = 256;
    
#ifdef MEDICION
    n = atoi(argv[1]);
#endif
    
    int dimension = sqrt(n);
    
    matriz<int> m(dimension, dimension);
    
    vector<int> v;
    
    chrono::high_resolution_clock::time_point t_antes, t_despues;
    unsigned long t_ejecucion = 0, t_medio;
    
    //Generamos matriz
    for(int i=0; i<dimension; ++i){
        v.clear();
        for (int j=0; j<dimension; ++j){
            v.insert(v.end(), (i*16)+j);
        }
        m.add(v); 
    }
    
#ifndef MEDICION
    //Mostramos la matriz original
    cout << "Matriz original:\n";
    m.draw();
    cout << endl;
#endif
    
    //Trasponemos la matriz y medimos el tiempo
#ifdef MEDICION
    
    for(int i=0; i<5; ++i){
        t_antes = chrono::high_resolution_clock::now();
        m.traspuesta();
        t_despues = chrono::high_resolution_clock::now();
        
        t_ejecucion += chrono::duration_cast<chrono::nanoseconds>(t_despues - t_antes).count();
    }
    t_medio = t_ejecucion/3;
    
#endif

#ifndef MEDICION
    m.traspuesta();

    cout << "Pulse enter para mostrar la matriz traspuesta\n" << endl;
    cin.ignore();
    
    //Mostramos la matriz traspuesta
    cout << "Matriz traspuesta:\n";
    m.draw(); 
#endif
    
#ifdef MEDICION
    cout << t_medio << endl;
#endif

    return 0;
}