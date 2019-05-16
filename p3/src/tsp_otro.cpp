#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>
#include <set>
#include "matriz.h"

using namespace std;


int main(int argc, char **argv){
    const double INF = numeric_limits<double>::max();

    if(argc < 2){
        cout << "ERROR. Faltan argumentos [archivo de datos]" << endl;
        exit(-1);
    }
    
    string output_filename = "data/output/";
    string input_filename;
    input_filename += argv[1];
    ifstream input_file(input_filename);
    input_filename.erase(0, 10);
    output_filename += input_filename;
    output_filename += "_otro.txt";
    
    string line;
    int num_ciudades;

    int ciudad;
    double coor_x, coor_y;
    vector<pair<double, double> > v_coordenadas;
    pair<double, double> coordenadas;

    vector<int> candidatos;
    vector<int> solucion;
    int tam_solucion;
    
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

    input_file.close();

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
    
    while(tam_solucion < num_ciudades){
        double mayor = INF * -1; // Valor de la coordenada y de la ciudad que está más al Norte
        int ciudad_mas_al_Norte;
        for(int i=0; i<num_ciudades; ++i){
            if ((v_coordenadas[i].second > mayor) && (candidatos[i] != -1)){
                ciudad_mas_al_Norte = i;
                mayor = v_coordenadas[i].second;
            }
        }
        solucion.push_back(ciudad_mas_al_Norte);
        candidatos[ciudad_mas_al_Norte] = -1;
        ++tam_solucion;
    }

    //Mostramos la solución
    cout << "Solucion: " << endl;

    for(int i=0; i<tam_solucion; ++i){
        cout << solucion[i]+1 << " ";
    }
    cout << endl;

    //Cálculo de la aumento_distancia total recorrida
    double distancia_recorrida = 0.00;
    for(int i=0; i<tam_solucion-1; ++i){
        distancia_recorrida += distancias[solucion[i]][solucion[i+1]];
    }

    cout << "Distancia total recorrida: " << distancia_recorrida << endl;
    
    
    //Salida de la solución a fichero
    ofstream output_file(output_filename);
    for(int i=0; i<tam_solucion; ++i){
        int c = solucion[i];
        output_file << c+1 << " " << v_coordenadas[c].first << " " << v_coordenadas[c].second << endl;
    }

    output_file.close();

    return (0);
}

    