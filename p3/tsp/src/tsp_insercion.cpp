#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>
#include "matriz.h"

using namespace std;

int minimo(vector<double> v){
    
}

int main(int argc, char **argv){
    const double INF = numeric_limits<double>::max();

    if(argc < 2){
        cout << "ERROR. Faltan argumentos [archivo de datos]" << endl;
        exit(-1);
    }
    
    ifstream input_file(argv[1]);
    string line;
    int dimension;

    int ciudad;
    double coor_x, coor_y;

    vector<pair<double, double> > v_coordenadas;
    pair<double, double> coordenadas;

    vector<int> candidatos;
    vector<int> solucion;
    
    //Movemos el offset a la linea en la que se dice la dimensión del grafo
    for(int i=0; i<3; ++i){
        getline(input_file, line);
    }

    getline(input_file, line);
    line.erase(0, 11);
    dimension = atoi(line.c_str());
    
    //Reservamos espacio para el grafo
    matriz <double> m(dimension, dimension, INF);

    //Movemos el offset al comienzo de los datos
    for(int i=0; i<3; ++i){
        getline(input_file, line);
    }

    //Tomamos los datos
    for (int i=0; i<dimension; ++i){
        input_file >> ciudad;
        input_file >> coor_x;
        input_file >> coor_y;
        coordenadas.first = coor_x;
        coordenadas.second = coor_y;
        v_coordenadas.push_back(coordenadas);
    }

    //Calculamos las distancias y las metemos en la matriz que representa
    //el grafo
    for(int i=0; i<dimension; ++i){
        for (int j=i+1; j<dimension; ++j){
            m(i,j)=sqrt(pow(v_coordenadas[j].first + v_coordenadas[i].first, 2) +
                        pow(v_coordenadas[j].second + v_coordenadas[i].second, 2));
            m(j,i)=m(i,j);
        }
    }

    //Generamos vector de candidatos
    for(int i=0; i<dimension; ++i)
        candidatos.push_back(i);
    
    //Elegimos el recorrido inicial
    int E = 0, O = 0, N = 0;
    double mas_al_E = v_coordenadas[0].second;
    double mas_al_O = v_coordenadas[0].second; 
    double mas_al_N = v_coordenadas[0].first;
    
    for(int i=1; i<dimension; ++i){
        if(v_coordenadas[i].first > mas_al_N){
            mas_al_N = v_coordenadas[i].first;
            N = i;
        }
        else if(v_coordenadas[i].second > mas_al_E){
            mas_al_E = v_coordenadas[i].second;
            E = i;
        }
        else if(v_coordenadas[i].second < mas_al_O){
            mas_al_O = v_coordenadas[i].second;
            O = i;
        }
    }
    
    solucion.push_back(O);
    solucion.push_back(N);
    solucion.push_back(E);
    
    //Comienza el algoritmo
    int insertados = 3;
    while(insertados < dimension){
        
        int minimo = 0;
        
        for(int i=0; i<insertados; ++i){
            for (int j=0; j<dimension; ++j){
            }
        }
    }
    

    

    return (0);
}
