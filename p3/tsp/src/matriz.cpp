

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   matriz.cpp
 * Author: nacho
 * 
 * Created on 1 de abril de 2019, 8:48
 */

#ifndef MATRIZ_CPP
#define MATRIZ_CPP

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include "matriz.h"

using namespace std;



////////////////////////////////////////////////////////////////////////////
template <class T>
matriz<T>::matriz() {
    f_capacity=filas=0;
    c_capacity=cols=0;  
}
////////////////////////////////////////////////////////////////////////////
template <class T>
matriz<T>::matriz(const int _filas, const int _cols){
    
    reserve(_filas, _cols);
    filas = 0;
    cols = 0;
}
////////////////////////////////////////////////////////////////////////////
template <class T>
matriz<T>::matriz(const int _filas, const int _cols, const T& _ini){
    
    reserve(_filas, _cols);
    filas = _filas;
    cols = _cols;
    
    for(int i=0; i<filas; ++i){
        for(int j=0; j<filas; ++j)
            m[i][j]=_ini;
    }
    
}
////////////////////////////////////////////////////////////////////////////
template <class T>
matriz<T>::matriz(const matriz& orig){  
}
////////////////////////////////////////////////////////////////////////////
template <class T>
matriz<T>::~matriz(){
    for (int i=0; i<m.capacity(); ++i){
        m[i].clear();
    }
    m.clear();
}
////////////////////////////////////////////////////////////////////////////
template <class T>
void matriz<T>::reserve(const int _filas, const int _cols){
    m.reserve(_filas);
    for (int i=0; i<_filas; ++i)
        m[i].reserve(_cols);
    
    f_capacity = _filas;
    c_capacity = _cols;
}
////////////////////////////////////////////////////////////////////////////
template <class T>
void matriz<T>::resize(int _filas, int _cols){
    m.resize(_filas);
    for(int i=0; i<_filas; ++i){
        m[i].resize(_cols);
    }

    f_capacity = _filas;
    c_capacity = _cols;
}
////////////////////////////////////////////////////////////////////////////
template<class T>
void matriz<T>::assign(int f, int c, T& val){
    assert(f>0 && f<filas && c>0 && c<filas);
    m[f][c] = val;
}
////////////////////////////////////////////////////////////////////////////
template <class T>
void matriz<T>::draw() const{
    for(int i=0; i<filas; ++i){
        for(int j=0; j<cols; ++j)
            cout<< setw(7) << setprecision(4) << m[i][j];
        cout << endl << endl;
    }
}
////////////////////////////////////////////////////////////////////////////
template <class T>
position matriz<T>::end() const{
    position p{filas,cols};
    return p;
}
////////////////////////////////////////////////////////////////////////////
template<class T>
void matriz<T>::add(const vector<T>& v){
    assert(filas<f_capacity);
    if (filas == 0){
        assert(v.size()<=c_capacity);
        cols = v.size();
    }
    else
        assert(v.size()<=c_capacity);
    
    m.insert(m.end(),v);
    filas++;
}
////////////////////////////////////////////////////////////////////////////
template <class T>
void matriz<T>::swap(const position& p_1, const position& p_2){
    T aux = m[p_1.fila][p_1.col];
    m[p_1.fila][p_1.col]=m[p_2.fila][p_2.col];
    m[p_2.fila][p_2.col]=aux; 
}
////////////////////////////////////////////////////////////////////////////
template <class T>
matriz<T>& matriz<T>::swap_submatrix(position p_1, position p_2, int dimension){
    position _p_1 = p_1;
    position _p_2 = p_2;

    int num_filas = 0;
    while(num_filas != dimension){

        int num_cols = 0;

        //swap de una fila
        while (num_cols != dimension){ //Hasta llegar al final de la submatriz
            swap(_p_1, _p_2);
            _p_1.col++;
            _p_2.col++;
            num_cols++;
        }
        //Siguiente fila
        num_filas++;
        _p_1.fila++;
        _p_2.fila++;
        //La posicion de las columnas vuelve a 0
        _p_1.col = p_1.col;
        _p_2.col = p_2.col;
    }
    
    return *this;
}
////////////////////////////////////////////////////////////////////////////
template <class T>
void matriz<T>::traspuestaDyV_arg(int dimension, position pos){
    
    
    if (dimension>1){
        int fmitad = pos.fila+(dimension/2);
        int cmitad = pos.col+(dimension/2);
        int dim_submatrix = dimension/2;
        position p_1{pos.fila, cmitad};
        position p_2{fmitad, pos.col};
        swap_submatrix(p_1, p_2, dim_submatrix);
        
        //
        traspuestaDyV_arg(dim_submatrix, pos);
        //
        position pos_1{pos.fila, cmitad};
        traspuestaDyV_arg(dim_submatrix, pos_1);
        //
        position pos_2{fmitad, pos.col};
        traspuestaDyV_arg(dim_submatrix, pos_2);
        //
        position pos_3{fmitad, cmitad};
        traspuestaDyV_arg(dim_submatrix, pos_3);
    } 
}
////////////////////////////////////////////////////////////////////////////
template <class T>
void matriz<T>::traspuestaDyV(){
    if((filas==cols) && ((filas*cols)%2 == 0)){ //Si es cuadrada y su tamaño es potencia de dos
        traspuestaDyV_arg(filas);
    }
}
////////////////////////////////////////////////////////////////////////////
template <class T>
void matriz<T>::traspuesta(){
    for(int i=0; i<filas; ++i){
        for(int j=i+1; j<cols; ++j){
            position p_1{i,j};
            position p_2{j,i};
            swap(p_1,p_2);
        }
    }
}
////////////////////////////////////////////////////////////////////////////
template <class T>
T& matriz<T>::operator ()(const int _fila, const int _col){
    return m[_fila][_col];
}
////////////////////////////////////////////////////////////////////////////
template <class T>
vector<T>& matriz<T>::operator [](const int fila){
    return m[fila];
}


#endif /*MATRIZ_CPP*/
