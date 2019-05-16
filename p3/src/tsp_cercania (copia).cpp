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


/*  FUNCION
 *  Esta funcion recibe como parametros un vector, que son las distintas distancias
 * a las distintas ciudades desde una misma ciudad y el vector candidatos para comprobar 
 * si ya se han visitado las respectivas ciudades.
 * 
 * La funcion encuentra el menor elemento del vector v y devuelve la posicion dentro
 * del vector de dicho elemento.
 
 
 */
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

    // Declaramos los vectores que albergaran los conjuntos Candidato y Solucion
    vector<int> solucion;
    vector<int> candidatos;

    // Inicializamos el conjunto de candidatos, el rango sera [0,15]. 
    for(int i = 0; i<dimension;++i){
      candidatos.push_back(i);
    }

    // Abergamos la primera ciudad en el conjunto solucion.
    int i = 0;
    solucion.push_back(0);
    candidatos[0] = -1;
    
    // variable donde guardaremos el indice, es decir, la ciudad a donde nos dirigimos.
    int menor;

    /*CUERPO DEL ALGORITMO:
     * La idea es encontrar la ciudad mas cercana haciendo uso de la matriz de
     * distancias. Una vez encontrada la ciudad (indice) al que nos dirigimos,
     * la posicion candidatos[indice] lo hacemos -1 para mostrar que esa ciudad
     * ya la hemos visitado y introducimos el indice en el vector de soluciones.
     * 
     * Para concluir, asignamos el valor del indice a la variable i para empezar
     * de nuevo todo el proceso
     */
    while(solucion.size()< dimension   ){
        vector <double> c;
        m.get_Fila(i,c);
      menor =BuscaMenor(c, candidatos);
      solucion.push_back(menor);
      candidatos[menor] = -1;
      i = menor;
    }
    
    // Imprimimos el vector solucion teniendo en cuenta que para la implementacion
    // La ciudad numero 1 ha sido el indice numero 0, por lo tanto tenemos que sumar
    // 1 a los valores del vector solucion.
    
    for(int i = 0; i< solucion.size();i++){
      cout << solucion [i]  + 1<< " --> ";
    }
    // Añadimos la ciudad inicial para indicar que completamos un ciclo.
   cout << " 1 " << " FIN.";
        
   
   // Volcamos la salida a un fichero para su visualizacion con la ayuda de 
   // GNUPLOT.
   
    ofstream ficherosalida("data/ulysses_camino.txt");
    for (int i = 0; i < dimension; ++i){
        int c = solucion[i];
        ficherosalida << c+1 << " " << v[c].first << " " << v[c].second << endl;
    }

    
    //FIN.
    return (0);
}
