//
// Created by Piotr Kuchnowski on 21.03.2023.
//

#ifndef UNTITLED_DYNAMICMATRIX_H
#define UNTITLED_DYNAMICMATRIX_H

#include <iostream>

/*This class represents graph as an dynamic matrix (two-dimensional array)
 * If value on [i][j] equals INT_MAX, there is no edge connecting vertices i and j */

class Matrix{
public:
    int verticesCount = 0;
    int** matrix = nullptr;

    void initialize(int size);                      //function that initializes list, freeing up memory occupied by previous lists
    void insert(int row, int column, int data);     //function that inserts neighbour to a given position in the matrix
    int getSize();                                  //function that returns verticesCount
    int getValue(int row, int column);              //function that returns a value from a given position in the matrix

    ~Matrix(){
        for(int i = 0; i < verticesCount; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
        std::cout <<"Destructor \n";
    }
};

#endif //UNTITLED_DYNAMICMATRIX_H
