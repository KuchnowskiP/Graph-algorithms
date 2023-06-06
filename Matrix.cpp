//
// Created by kuchn on 21.03.2023.
//
#include "Matrix.h"
#include <string>
#include <limits.h>

void Matrix::initialize(int size) {
    for(int i = 0; i < verticesCount; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    verticesCount = size;
    matrix = new int*[verticesCount];
    for(int i = 0; i < verticesCount; i++){
        matrix[i] = new int[verticesCount];
        for(int j = 0; j < verticesCount; j++){
            matrix[i][j] = INT_MAX;
        }
    }
}

void Matrix::insert(int row, int column, int data){
    matrix[row][column] = data;
}

int Matrix::getSize() {
    return verticesCount;
}

int Matrix::getValue(int row, int column) {
    return matrix[row][column];
}




