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

double Distancia(const pair<double,double> & posicion_A,
                 const pair<double,double> &posicion_B){

  double distancia = sqrt(pow(posicion_A.first - posicion_B.first,2) +
                      pow(posicion_A.second-posicion_B.second,2));

  return distancia;
}

int Buscar(vector<int> v, int n){
    int inicio = 0;
    int fin = v.size()-1;

    while ((inicio != fin)){
        if(v[inicio] == n){
            return inicio;
        }
        if(v[fin] == n){
            return fin;
        }
    }

    return -1;
}

/**
 * @brief Estructura que representa una arista del grafo
 * @param a Una ciudad del grafo
 * @param b Otra ciudad del grafo
 * @param distancia Distancia entre la ciudad a y b
 */
struct Arista{
    int a;
    int b;
    double distancia;
};

struct aristaComparator{

    bool operator ()(const Arista arista1, const Arista arista2) const{
        if (arista1.distancia < arista2.distancia)
            return true;
        else 
            return false;
    }
};

typedef set<Arista,aristaComparator> Set_Aristas;
typedef set<Arista, aristaComparator>::iterator Set_Aristas_iterator;

/**
 * Este programa busca un ciclo que recorra todas las ciudades de 
 * un mapa mediante un algoritmo de tipo greedy. En esta versión
 * del algoritmo, dado un recorrido inicial que contiene tres nodos
 * en cada paso se busca el nodo más cercano al conjunto solución que
 * se encuentre en el conjunto de candidatos. El nodo más cercano es
 * insertado en la posición del vector que menos aumente el recorrido.
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
    vector<Arista> solucion_aristas;
    
    //Movemos el offset a la linea en la que se dice la dimensión del grafo
    for(int i=0; i<3; ++i){
        getline(input_file, line);
    }

    getline(input_file, line);
    line.erase(0, 11);
    num_ciudades = atoi(line.c_str());
    
    //Reservamos espacio para el grafo
    matriz <double> distancias(num_ciudades, num_ciudades, 0);
    Set_Aristas aristas;

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

    //Ordenamos las aristas del grafo de menor a mayor
    for(int i=0; i<num_ciudades; ++i){
        for (int j=i+1; j<num_ciudades; ++j){
            Arista a{i, j, Distancia(v_coordenadas[i], v_coordenadas[j])};
            aristas.insert(a);
        }
    }

    //Vector con el grado de cada nodo del grafo solución
    vector<int> grado(num_ciudades);
    grado.insert(grado.begin(), num_ciudades, 0);    

    //Generamos vector de candidatos
    for(int i=0; i<num_ciudades; ++i)
        candidatos.push_back(i);
    

    int tam_solucion = solucion_aristas.size(); //Tamaño del conjunto solucion

    Set_Aristas_iterator it = aristas.begin();
    while(tam_solucion < num_ciudades-1){
        bool valido = false;
        while((!valido) && (it!=aristas.end())){
            if(grado[(*it).a] < 2 && grado[(*it).b] < 2){
                valido = true;
                solucion_aristas.push_back(*it);
                ++tam_solucion;
                grado[(*it).a]++;
                grado[(*it).b]++;
            }
                
            
            ++it;
        }        
    }

    //Mostramos la solución
    cout << "Solucion: " << endl;

    for(int i=0; i<tam_solucion; ++i){
        cout << solucion_aristas[i].a + 1 << " - " << solucion_aristas[i].b + 1 << endl;
    }
    cout << endl;

    //Cálculo de la distancia total recorrida
    double distancia_recorrida = 0.00;
    for(int i=0; i<tam_solucion-1; ++i){
        distancia_recorrida += distancias[i][i+1];
    }

    cout << "Distancia total recorrida: " << distancia_recorrida << endl;
    
    //Salida de la solución a fichero
    ofstream output_file("data/ulysses16_aristas.txt");
    for(int i=0; i<tam_solucion; ++i){
        int c = solucion[i];
        output_file << c+1 << " " << v_coordenadas[c].first << " " << v_coordenadas[c].second << endl;
    }

    return (0);
}
