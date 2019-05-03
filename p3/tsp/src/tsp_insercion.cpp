#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>
#include "matriz.h"

using namespace std;

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

    distancias.draw();

    //Generamos vector de candidatos
    for(int i=0; i<num_ciudades; ++i)
        candidatos.push_back(i);
    
    //Elegimos el recorrido inicial
    int E = 0, O = 0, N = 0;
    double mas_al_E = v_coordenadas[0].second;
    double mas_al_O = v_coordenadas[0].second; 
    double mas_al_N = v_coordenadas[0].first;
    
    for(int i=1; i<num_ciudades; ++i){
        if(v_coordenadas[i].first > mas_al_N){
            mas_al_N = v_coordenadas[i].first;
            N = i;
        }
        if(v_coordenadas[i].second > mas_al_E){
            mas_al_E = v_coordenadas[i].second;
            E = i;
        }
        if(v_coordenadas[i].second < mas_al_O){
            mas_al_O = v_coordenadas[i].second;
            O = i;
        }
    }
    
    solucion.push_back(O); candidatos[O] = -1;
    solucion.push_back(N); candidatos[N] = -1;
    solucion.push_back(E); candidatos[E] = -1;
    
    cout << "Recorrido inicial: " << endl;
    for(int i=0; i<3; ++i){
        cout << solucion[i]+1 << " ";
    }
    cout << endl << "insertados:" << endl;
    //Comienza el algoritmo

    vector<int>::iterator sol_it, cand_it, ciudad_origen_it;

    int tam_solucion = 3;    
    while(tam_solucion < num_ciudades){
        //Buscamos la ciudad más cercana al conjunto solución
        //int ciudad_origen = 0;
        int ciudad_mas_cercana = 0;
        double distancia_mas_cercana = INF;

        for(sol_it=solucion.begin(); sol_it!=solucion.end(); ++sol_it){
            for (cand_it=candidatos.begin(); cand_it!=candidatos.end(); ++cand_it){
                if ((distancias[*sol_it][*cand_it] < distancia_mas_cercana) && (*cand_it != -1)){
                    ciudad_origen_it = sol_it;
                    ciudad_mas_cercana = *cand_it;
                    distancia_mas_cercana = distancias[*sol_it][*cand_it];
                }
            }
        }

        //TODO
        //Una vez encontrada vemos en que posición del conjunto solución insertarla
        //para minimizar el trayecto

        vector<int>::iterator ciudad_siguiente_it = ciudad_origen_it;
        vector<int>::iterator ciudad_anterior_it = ciudad_origen_it;
        vector<int>::iterator final_it = solucion.end();
        final_it--;

        if(ciudad_origen_it == solucion.begin()){
            ++ciudad_siguiente_it;
            ciudad_anterior_it = final_it;
        }
        else if(ciudad_origen_it == final_it){
            ciudad_siguiente_it = solucion.begin();
            --ciudad_anterior_it;
        }
        else{
            ++ciudad_siguiente_it;
            --ciudad_anterior_it;
        }

        if(distancias[ciudad_mas_cercana][*ciudad_anterior_it] < distancias[ciudad_mas_cercana][*ciudad_siguiente_it]){
            solucion.insert(ciudad_origen_it, ciudad_mas_cercana);
        }
        else{
            solucion.insert(ciudad_siguiente_it, ciudad_mas_cercana);
        }

        cout << ciudad_mas_cercana+1 << endl;

        candidatos[ciudad_mas_cercana] = -1;
        tam_solucion++;
        for(int i=0; i<tam_solucion; ++i){
            cout << solucion[i]+1 << " ";
        }
        cout << endl;
    }

    cout << "Solucion: " << endl;

    for(int i=0; i<tam_solucion; ++i){
        cout << solucion[i]+1 << " ";
    }
    cout << endl;
    
    ofstream output_file("data/camino.txt");
    for(int i=0; i<num_ciudades; ++i){
        int c = solucion[i];
        output_file << c+1 << " " << v_coordenadas[c].first << " " << v_coordenadas[c].second << endl;
    }

    return (0);
}
