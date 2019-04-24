/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: nacho
 *
 * Created on 14 de marzo de 2019, 15:59
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <cassert>
#include <climits>

using namespace std;

int pivotar(double *v, const int ini, const int fin){
    double pivote = v[ini], aux;
    int i = ini+1, j = fin;

    while(i<=j){
        while(v[i]<pivote && i<=j) i++;
        while(v[j]>=pivote && j>=i) j--;

        if (i<j){
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }

    if (j > ini){
        v[ini] = v[j];
        v[j] = pivote;
    }

    return j;
}
/****************************************************************************/
int Busqueda(int *v, int n, int elem){
  int inicio, fin, centro;

  inicio = 0;
  fin = n-1;
  centro = (inicio+fin)/2;

  while ((inicio<=fin) && (v[centro] != elem)){

    if (elem<v[centro])
      fin = centro-1;
    else{
      inicio = centro+1;
    }
    centro = (inicio+fin)/2;
  }

  if (inicio > fin)
    return -1;

  return centro;
}
/****************************************************************************/
void EliminaRepetidos (double original[], int & nOriginal) {
  int i, j, k;

  for (i=0; i<nOriginal; ++i){
    j = i+1;

    do{
      if (original[j] = original[i]){
        for (k=j+1; k<nOriginal; k++)
          original[k-1] = original[k];

          nOriginal--;
      }
      else
        j++;
    }while (j<nOriginal);
  }
}
/****************************************************************************/
void hanoi (int M, int i, int j){
  if (M > 0)
    {
      hanoi(M-1, i, 6-i-j);
      hanoi (M-1, 6-i-j, j);
  }
}
/****************************************************************************/
void pintaVector(int *v, int n){
  for (int i=0; i<n; ++i){
    cout << " | "<< v[i];
  }
  cout << endl;
}

void reajustar(int *T, int n, int k){
  int j, v;
  v=T[k];
  bool esAPO = false;

  while((k < n/2) && !esAPO){
    j = k*2+1;
    if ((j < (n-1)) && (T[j] < T[j+1]))
      j++;

    if (v >= T[j])
      esAPO = true;

    T[k] = T[j];
    k = j;

  }

  T[k] = v;
}

void heapsort(int *v, int n){
  int i;

  for (i=n/2; i>=0; i--){
    reajustar(v, n, i);
  }



  for (i=n-1; i>=1; i--){
    int aux = v[0];
    v[0] = v[i];
    v[i] = aux;
    reajustar(v, i, 0);
  }
}
/****************************************************************************/
void OrdenaBurbuja(int *v, int n) {

	int i, j, aux;
	bool haycambios= true;

	i= 0;
	while (haycambios) {

	 haycambios=false; // Suponemos vector ya ordenado
	 for (j= n-1; j>i; j--) { // Recorremos vector de final a i

		 if (v[j-1]>v[j]) { // Dos elementos consecutivos mal ordenados
		  aux= v[j]; // Los intercambiamos
		  v[j]= v[j-1];
		  v[j-1]= aux;
		  haycambios= true; // Al intercambiar, hay cambio
		 }
	 }
	}
}

/****************************************************************************/

/* ************************************************************ */
/*  Método de ordenación por mezcla  */

/**
   @brief Ordena un vector por el método de mezcla.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de mezcla.
*/
inline static
void mergesort(int T[], int num_elem);



/**
   @brief Ordena parte de un vector por el método de mezcla.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar.
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la mezcla.
*/
static void mergesort_lims(int T[], int inicial, int final);


/**
   @brief Ordena un vector por el método de inserción.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserción.
*/
inline static
void insercion(int T[], int num_elem);


/**
   @brief Ordena parte de un vector por el método de inserción.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar.
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la inserción.
*/
static void insercion_lims(int T[], int inicial, int final);


/**
   @brief Mezcla dos vectores ordenados sobre otro.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a escribir.
   @param final: Posición detrás de la última de la parte del
                   vector a escribir
		   inicial < final.
   @param U: Vector con los elementos ordenados.
   @param V: Vector con los elementos ordenados.
             El número de elementos de U y V sumados debe coincidir
             con final - inicial.

   En los elementos de T entre las posiciones inicial y final - 1
   pone ordenados en sentido creciente, de menor a mayor, los
   elementos de los vectores U y V.
*/
static void fusion(int T[], int inicial, int final, int U[], int V[]);
const int UMBRAL_MS = 100;
inline static void insercion(int T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}


static void insercion_lims(int T[], int inicial, int final)
{
  int i, j;
  int aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}

void mergesort(int T[], int num_elem)
{
  mergesort_lims(T, 0, num_elem);
}

static void mergesort_lims(int T[], int inicial, int final)
{
  if (final - inicial < UMBRAL_MS)
    {
      insercion_lims(T, inicial, final);
    } else {
      int k = (final - inicial)/2;

      int * U = new int [k - inicial + 1];
      assert(U);
      int l, l2;
      for (l = 0, l2 = inicial; l < k; l++, l2++)
        U[l] = T[l2];
      U[l] = INT_MAX;

      int * V = new int [final - k + 1];
      assert(V);
      for (l = 0, l2 = k; l < final - k; l++, l2++)
        V[l] = T[l2];
      V[l] = INT_MAX;

      mergesort_lims(U, 0, k);
      mergesort_lims(V, 0, final - k);
      fusion(T, inicial, final, U, V);
      delete [] U;
      delete [] V;
    };
}


static void fusion(int T[], int inicial, int final, int U[], int V[])
{
  int j = 0;
  int k = 0;
  for (int i = inicial; i < final; i++)
    {
      if (U[j] < V[k]) {
	T[i] = U[j];
	j++;
      } else{
	T[i] = V[k];
	k++;
      };
    };
}


/*
 *
 */
int main(int argc, char** argv) {
    srand(time(NULL));
    int n = atoi(argv[1]);

    int *v = new int [n];

    using namespace chrono;
    high_resolution_clock::time_point t_antes, t_despues;
    unsigned long t_ejecucion, sum = 0;

    for (int j=0; j<3; ++j){

      for (int i=0; i<n; ++i){
          v[i] = rand()%n;
      }

      t_antes = high_resolution_clock::now();
      mergesort(v, n);
      t_despues = high_resolution_clock::now();

      sum += duration_cast<chrono::nanoseconds>(t_despues - t_antes).count();
    }

    t_ejecucion = sum/3;


    cout << setw(8) << n << setw(12) << t_ejecucion << endl;

    delete [] v;

    return 0;
}
