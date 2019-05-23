#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>
#include "matriz.h"
#include <iomanip>

using namespace std;
const double INF = numeric_limits<double>::max();


double Distancia(const pair<double,double> & posicion_A,
                 const pair<double,double> &posicion_B){

  double distancia = sqrt(pow(posicion_A.first - posicion_B.first,2) +
                      pow(posicion_A.second-posicion_B.second,2));

  return distancia;
}

//TODO
int BuscarGasolinera(const int autonomia,const int pos_actual, const int ciudad_destino, matriz<double> & grafo,  vector<int> &candidatos){

  int parada = -1;
  vector<int> indices_posibles_gasolineras;
  double minimo = INF;

  for (int i = 0 ;i <candidatos.size();++i){
    double distancia_actual_candidato = grafo[pos_actual][i];
    double distancia_candidato_destino = grafo[i][ciudad_destino];
    if((distancia_actual_candidato <= autonomia) && (candidatos[i] != -1)
      && (distancia_candidato_destino < minimo)){
      parada = i;
      minimo = distancia_candidato_destino;
    }
  }

  return(parada);
}

int main(int argc, char **argv){

    
    string line;
    int num_ciudades;

    if(argc<5){
      cout << "Faltan argumentos:\n"
              "./gasolineras [archivo] [autonomia] [ciudad origen] [ciudad destino]"
           << endl;
    }

    ifstream input_file(argv[1]);
    double autonomia = atoi(argv[2]);
    int ciudad_origen = atoi(argv[3]) - 1;
    int ciudad_destino = atoi(argv[4]) - 1;
    int pos_actual = ciudad_origen;

    //Variables que usaremos para crear la matriz de distancias (grafo)
    int ciudad;
    double coor_x, coor_y;
    vector<pair<double, double> > v_coordenadas;
    pair<double, double> p;

    //Movemos el offset a la linea en la que se dice la dimensión del grafo
    for(int i=0; i<3; ++i){
      getline(input_file, line);
    }

    getline(input_file, line);
    line.erase(0, 11);
    num_ciudades = atoi(line.c_str());

    //Reservamos espacio para el grafo
    matriz<double> distancias(num_ciudades, num_ciudades, 0);


    //Movemos el offset al comienzo de los datos
    for(int i=0; i<3; ++i){
      getline(input_file, line);
    }

    //Tomamos los datos
    for (int i=0; i<num_ciudades; ++i){
      input_file >> ciudad;
      input_file >> coor_x;
      input_file >> coor_y;
      p.first = coor_x;
      p.second = coor_y;
      v_coordenadas.push_back(p);
    }

    //Calculamos las distancias y las metemos en la matriz que representa
    //el grafo
    for(int i=0; i<num_ciudades; ++i){
      for (int j=i+1; j<num_ciudades; ++j){
        distancias[i][j]=Distancia(v_coordenadas[i], v_coordenadas[j]);
        distancias[j][i]=distancias[i][j];
      }
    }

    //Comienzo del algoritmo
    vector<int> candidatos;
    vector<int> solucion;
    solucion.push_back(ciudad_origen);

    for(int i = 0; i< num_ciudades; i++)
      candidatos.push_back(i);

    candidatos[ciudad_origen] = -1;
    bool fin = false;
    pos_actual = ciudad_origen;


    while(fin == false){

      if(autonomia >= distancias[pos_actual][ciudad_destino]){
        cout << "FIN = DESTINO" <<  endl;
        solucion.push_back(ciudad_destino);
        fin = true;
      }

      else{
        pos_actual = BuscarGasolinera(autonomia,pos_actual, ciudad_destino, distancias, candidatos);

        if(pos_actual != -1){
          candidatos[pos_actual] = -1;
          solucion.push_back(pos_actual);
        }else{
          cout << "No podemos llegar a ninguna otra gasolinera" << endl;
          fin = true;
        }

      }
    }

    for (int i = 0; i<solucion.size(); ++i){
      cout << solucion[i]+1 << " --> ";
    }

    cout << "FIN" << endl;

    ofstream ficherosalida("data/gasolineras.txt");
    for (int i = 0; i < solucion.size(); ++i){
        int c = solucion[i];
        ficherosalida << c+1 << " " << v_coordenadas[c].first << " " << v_coordenadas[c].second << endl;
    }

    return(0);
}
