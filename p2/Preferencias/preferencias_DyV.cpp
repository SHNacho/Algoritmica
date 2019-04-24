/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: nacho
 *
 * Created on 11 de abril de 2019, 19:56
 */

#include <cstdlib>
#include <iostream>
#include <chrono>
#include<stdlib.h>
#include<time.h>
#include <iomanip>
#include <cassert>

using namespace std;

void draw(int *v, int tam){
    for (int i=0; i<tam; ++i){
        cout << v[i] << "  ";
    }
    cout << endl;
}

//generador de ejemplos para el problema de la comparación de preferencias.
//Simplemente se genera una permutación aleatoria del vector 0,1,2,...,n-2,n-1

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
int merge(int arr[], int l, int m, int r) 
{ 
    int n_inversiones = 0;
    int i, j, k; 
    int n1 = m - l + 1; //Tamaño vector L
    int n2 =  r - m; //Tamaño vector R
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            n_inversiones += n1-i;
            j++; 
            
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    }
    
    return n_inversiones;
} 
  

int Inversiones(int arr[], int l, int r, int & n_inversiones) 
{ 
    if (l < r) 
    { 
         
        int m = l+(r-l)/2; 
  
        // Cuenta las inversiones de las dos mitades
        Inversiones(arr, l, m, n_inversiones); 
        Inversiones(arr, m+1, r, n_inversiones); 
  
        n_inversiones += merge(arr, l, m, r); 
    } 
    
    return n_inversiones;
} 


/*
 * 
 */
int main(int argc, char** argv) {
    
    int n = 1000;
    int inversiones = 0;
    
#ifdef M
    if(argc < 2){
        cout << "Faltan argumentos (Tamaño del vector)" << endl;
        exit(-1);
    }
    
    n = atoi(argv[1]);   
    
    chrono::high_resolution_clock::time_point t_antes, t_despues;
    unsigned long t_ejecucion = 0, t_medio;
#endif
    
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
    
    
    
#ifdef M
    for(int i=0; i<5; ++i){
       t_antes = chrono::high_resolution_clock::now();
       Inversiones(v, 0, n-1, inversiones);
       t_despues = chrono::high_resolution_clock::now();

       t_ejecucion += chrono::duration_cast<chrono::nanoseconds>(t_despues - t_antes).count();
    }
    t_medio = t_ejecucion/5;

    cout << t_medio << endl;
#endif
    
    cout << "Vector:" << endl;
    
    draw(v, n);
    
    Inversiones(v, 0, n-1, inversiones);
    
    cout << "El número de inversiones es:" << inversiones << endl;
    
    return 0;
}
