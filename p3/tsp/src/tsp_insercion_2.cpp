#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>
#include "matriz.h"

using namespace std;

/**
 * Este programa busca un ciclo que recorra todas las ciudades de 
 * un mapa mediante un algoritmo de tipo greedy. En esta versión
 * del algoritmo, dado un recorrido inicial que contiene tres nodos,
 * en cada paso se busca el nodo que menos aumenta el tamaño del recorrido
 * y es insertado en la posición en la que cumple esta condición.
 */
int main(int argc, char **argv){
    const double INF = numeric_limits<double>::max();

    if(argc < 2){
        cout << "ERROR. Faltan argumentos [archivo de datos]" << endl;
        exit(-1);
    }
    
    ifstream input_file(argv[1]);
    string line;
    int num_ciudades;

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
    num_ciudades = atoi(line.c_str());
    
    //Reservamos espacio para el grafo
    matriz <double> distancias(num_ciudades, num_ciudades, 0);

    //Movemos el offset al comienzo de los datos
    for(int i=0; i<3; ++i){
        getline(input_file, line);
    }

    //Tomamos los datos
    for (int i=0; i<num_ciudades; ++i){
        input_file >> ciudad;
        input_file >> coor_x;
        input_file >> coor_y;
        coordenadas.first = coor_x;
        coordenadas.second = coor_y;
        v_coordenadas.push_back(coordenadas);
    }

    //Calculamos las distancias y las metemos en la matriz que representa
    //el grafo
    for(int i=0; i<num_ciudades; ++i){
        for (int j=i+1; j<num_ciudades; ++j){
            distancias[i][j]=sqrt(pow(v_coordenadas[j].first - v_coordenadas[i].first, 2) +
                        pow(v_coordenadas[j].second - v_coordenadas[i].second, 2));
            distancias[j][i]=distancias[i][j];
        }
    }

    //Generamos vector de candidatos
    for(int i=0; i<num_ciudades; ++i)
        candidatos.push_back(i);
    
    //Elegimos el recorrido inicial
    int E = 0, O = 0, N = 0;
    double mas_al_E = v_coordenadas[0].first;
    double mas_al_O = v_coordenadas[0].first; 
    double mas_al_N = v_coordenadas[0].second;
    
    for(int i=1; i<num_ciudades; ++i){
        if(v_coordenadas[i].second > mas_al_N){
            mas_al_N = v_coordenadas[i].second;
            N = i;
        }
        if(v_coordenadas[i].first > mas_al_E){
            mas_al_E = v_coordenadas[i].first;
            E = i;
        }
        if(v_coordenadas[i].first < mas_al_O){
            mas_al_O = v_coordenadas[i].first;
            O = i;
        }
    }
    
    solucion.push_back(O); candidatos[O] = -1;
    solucion.push_back(N); candidatos[N] = -1;
    solucion.push_back(E); candidatos[E] = -1;

    int tam_solucion = solucion.size(); //Tamaño del conjunto solucion

    //Comienzo del algoritmo
    vector<int>::iterator sol_it, cand_it;  //Iteradores de los vectores de candidatos y solución

    //Buscamos la ciudad que menos aumenta el tamaño del recorrio
    while(tam_solucion < num_ciudades){

        int ciudad_insertada;
        vector<int>::iterator pos_insercion;
        double distancia_minima = INF;

        for(cand_it = candidatos.begin(); cand_it != candidatos.end(); ++cand_it){
            if(*cand_it != -1){
                for(sol_it=solucion.begin(); sol_it!=solucion.end(); ++sol_it){
                    //Tenemos en cuenta que es un ciclo por lo que la ciudad siguiente al
                    //ultimo elemento del conjunto solución es el primer elemento
                    vector<int>::iterator ciudad_siguiente = sol_it;
                    if(sol_it == --solucion.end())
                        ciudad_siguiente = solucion.begin();
                    else
                        ++ciudad_siguiente;

                    double distancia = distancias[*sol_it][*cand_it]+distancias[*cand_it][*ciudad_siguiente];
                    if(distancia < distancia_minima){
                        ciudad_insertada = *cand_it;
                        distancia_minima = distancia;
                        pos_insercion = ciudad_siguiente;
                    }
                }  
            }
        }
        
        solucion.insert(pos_insercion, ciudad_insertada);
        candidatos[ciudad_insertada] = -1;
        ++tam_solucion;
        
    }    

    //Insertamos de nuevo el primer elemento del conjunto solución
    // ya que es un caamino cerrado
    solucion.push_back(*solucion.begin());

    //Mostramos la solución
    cout << "Solucion: " << endl;

    for(int i=0; i<tam_solucion; ++i){
        cout << solucion[i]+1 << " ";
    }
    cout << endl;

    //Cálculo de la distancia total recorrida
    double distancia_recorrida = 0.00;
    for(int i=0; i<tam_solucion-1; ++i){
        distancia_recorrida += distancias[i][i+1];
    }

    cout << "Distancia total recorrida: " << distancia_recorrida << endl;
    
    //Salida de la solución a fichero
    ofstream output_file("data/ulysses16_insercion.txt");
    for(int i=0; i<num_ciudades; ++i){
        int c = solucion[i];
        output_file << c+1 << " " << v_coordenadas[c].first << " " << v_coordenadas[c].second << endl;
    }

    return (0);
}
