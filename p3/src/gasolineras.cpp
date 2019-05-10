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

int BuscarGasolinera(const int &autonomia,const pair<double,double> &pos_actual,
   const vector<double> &distancias_B, const vector<double>  &dist_actual, vector<int> &candidatos){

    int parada = -1;
    vector<int> indices_posibles_gasolineras;
    double minimo = INF;
    for (int i = 0 ;i <candidatos.size();++i){
        if(dist_actual[i]<=autonomia && candidatos[i] != -1){
            indices_posibles_gasolineras.push_back(i);
        }
    }

    if(!indices_posibles_gasolineras.empty()){
        for(int i = 0; i<indices_posibles_gasolineras.size();++i){
            if(distancias_B[indices_posibles_gasolineras[i]] < minimo)
                parada = indices_posibles_gasolineras[i];
        }
    }

return(parada);
}

int main(int argc, char **argv){

    
    string line;
    int dimension;

    if(argc<5){
      cout << "Faltan argumentos:\n"
              "./gasolineras [archivo] [autonomia] [ciudad origen] [ciudad destino]"
           << endl;
    }

    ifstream input_file(argv[1]);
    double autonomia = atoi(argv[2]);

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


    // Las posiciones de las dos ciudades las preestablecemos.

    pair<double,double> pos_actual, ciudad_A;
    pair<double,double> ciudad_B;

     ciudad_A.first = 35;
     ciudad_A.second = 10;

     ciudad_B.first = 41;
     ciudad_B.second = 15;

     vector<double> distancias_B;
     vector<double> distancias_actual;

     for(int i = 0; i<v.size();i++){
       distancias_B.push_back(Distancia(ciudad_B,v[i]));
     }

     vector<int> candidatos;
     vector<int> solucion;

     for(int i = 0; i< dimension; i++)
      candidatos.push_back(i);

      bool fin = false;
      int parada;

      pos_actual = ciudad_A;


      while(fin == false){

        if(autonomia>=Distancia(pos_actual,ciudad_B)){
            cout << "FIN = DESTINO" <<  endl;
          fin = true;
        }

        else{

          distancias_actual.clear();
          for(int i = 0; i<dimension;++i)
            distancias_actual.push_back(Distancia(pos_actual,v[i]));

          parada = BuscarGasolinera(autonomia,pos_actual,distancias_B,distancias_actual, candidatos);

          if(parada != -1){
            candidatos[parada] = -1;
            solucion.push_back(parada);
            pos_actual = v[parada];
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
        ficherosalida << c+1 << " " << v[c].first << " " << v[c].second << endl;
    }

    return(0);
}
