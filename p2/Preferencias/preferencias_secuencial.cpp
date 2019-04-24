/*
 * Cálculo del tiempo del algoritmo pivotar.
 */

#include <cstdlib>
#include <iostream>
#include <chrono>
#include<stdlib.h>
#include<time.h>
#include <iomanip>
#include <cassert>

using namespace std;

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

double similitud (int *vector1, int tamanio){

  double invertidos = 0;

  for (int i = 0; i < tamanio; ++i){
    for (int j = i+1; j < tamanio; ++j)
      if (vector1[i] > vector1[j])
        invertidos++;
  }

  return invertidos;
}

void pintar(int *v, int tam){
    for (int i=0; i<tam; ++i){
        cout << v[i] << "  ";
    }
    cout << endl;
}

int main (int argc, char** argv) {

    int n = 1000;
    int *v = new int [n];
    
    assert(v);
    srand(time(0));
    
    for (int j=0; j<n; j++)
        v[j]=j;
    //for (int j=0; j<n; j++) {cout << T[j] << " ";}
    //algoritmo de random shuffling the Knuth (permutaci�n aleatoria)
    for (int j=n-1; j>0; j--) {
        double u=uniforme();
        int k=(int)(j*u);
        int tmp=v[j];
        v[j]=v[k];
        v[k]=tmp;
    }
    
    pintar(v, n);
    
    int invertidos = similitud(v,n);

    cout << "El número de invertidos es: " << invertidos << endl;
    
    delete []v;

}
