/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   matriz.h
 * Author: nacho
 *
 * Created on 1 de abril de 2019, 8:48
 */

#ifndef MATRIZ_H
#define MATRIZ_H

#include<vector>
#include<iostream>

using namespace std;

struct position{
    int fila;
    int col;
};

 
template <class T>
class matriz{
    
private:        
    vector<vector<T> > m;
    int filas;
    int cols;
    int f_capacity;
    int c_capacity;
    
    /**
     * @brief Interecambia dos submatrices cuadradas de dimensin 'dimension'
     * dentro del vector
     * @param pos_1 posicion de comienzo de la primera submatriz
     * @param pos_2 posicion de comienzo de la segunda submatriz
     * @param dimension dimension de las submatrices.
     */
    matriz<T>& swap_submatrix(position p_1, position p_2, int dimension);

public:
    matriz();
    matriz(const matriz<T>& orig);
    matriz(const int _filas, const int _cols, const T& _ini);
    matriz(const int _filas, const int _cols);
    virtual ~matriz();
    
    /**
     * @brief Reserva espacio para la matriz
     * @param _filas Número de filas
     * @param _cols Número de columnas
     */
    void reserve(const int _filas, const int _cols);
    
    /**
     * @brief Modifica el tamaño de la matriz
     * @param _filas Nuevo número de filas
     * @param _cols Nuevo número de columnas
     */
    void resize(int _filas, int _cols);

    void assign(int f, int c, T& val);
    
    /**
     * @brief Pinta la matriz
     */
    void draw() const;
    
    /**
     * @brief Posición siguiente al último elemento de la matriz
     * @return Posición siguiente al último elemento de la matriz
     */
    position end() const;
    
    /**
     * @brief Añade un elemento al final de la matriz
     * @param elem Elemento a añadir
     * @return Posicion en la que se ha añadido el elemento
     */
    void add(const vector<T>& elem);
    
    /**
     * @brief intercambia la posición de dos elementos de la matriz
     * @param p_1 Posición del primer elemento
     * @param p_2 Posición del segundo elemento
     */
    void swap(const position& p_1, const position& p_2);
    
    /**
     * @brief Hace la traspuesta de la matriz cuadrada cuyo tamaño es potencia de 2
     */
    void traspuestaDyV_arg(int dimension=0, position pos = {0,0});
    
    /**
     * 
     */
    void traspuestaDyV();
    
    /**
     * 
     */
    void traspuesta();
    
    /**
     * 
     * @param _fila
     * @param _col
     * @return 
     */
    T& operator ()(const int _fila, const int _col);
    
    /**
     * @brief Sobrecarga del operador []
     * @param fila Fila de la matriz
     * @return Fila de la matriz nº fila
     */
    vector<T>& operator [](const int fila);
};

#include"../src/matriz.cpp"

#endif /* MATRIZ_H */

