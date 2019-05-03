#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>
#include "matriz.h"

using namespace std;
const double INF = numeric_limits<double>::max();


// Devuelve la posicion dentro del vector del elemento mas pequeño.
int BuscaMenor(vector<double> v, vector<int> & candidatos){
  int menor;
  double minimo = INF;
  for(int i = 0;i< v.size(); ++i){
    if( v[i] < minimo && candidatos[i] !=-1){
        minimo = v[i];
        menor = i;
    
    }

  }
  return(menor);
}

int main(int argc, char **argv){

    ifstream input_file(argv[1]);
    string line;
    int dimension;

    int ciudad;
    double coor_x, coor_y;

    vector<pair<double, double> > v;
    pair<double, double> p;

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
        p.first = coor_x;
        p.second = coor_y;
        v.push_back(p);
    }

    //Calculamos las distancias y las metemos en la matriz que representa
    //el grafo
    for(int i=0; i<dimension; ++i){
        for (int j=i+1; j<dimension; ++j){
            m[i][j]=sqrt(pow(v[j].first - v[i].first, 2) +
                        pow(v[j].second - v[i].second, 2));
            m[j][i]=m[i][j];
        }
    }

    //ALgoritmo basado en cercanias. La idea es ir a la ciudad mas cercana
    //sin formar un ciclo. Exceptuando la ultima.

    vector<int> solucion;
    vector<int> candidatos;

    for(int i = 0; i<dimension;++i){
      candidatos.push_back(i);
    }

    int i = 0;
    solucion.push_back(0);
    candidatos[0] = -1;
    
    int menor;

    while(solucion.size()< dimension   ){
        vector <double> c;
        m.get_Fila(i,c);
      menor =BuscaMenor(c, candidatos);
      solucion.push_back(menor);
      candidatos[menor] = -1;
      i = menor;



    }
    

    for(int i = 0; i< solucion.size();i++){
      cout << solucion [i]  + 1<< " --> ";
    }
    
    cout << "FIN";
    
    
    ofstream ficherosalida("data/ulysses_camino.txt");
    for (int i = 0; i < dimension; ++i){
        int c = solucion[i];
        ficherosalida << c+1 << " " << v[c].first << " " << v[c].second << endl;
    }












    return (0);
}
