//
// Created by kuchn on 21.03.2023.
//

#ifndef UNTITLED_DYNAMICMATRIX_H
#define UNTITLED_DYNAMICMATRIX_H

#include <iostream>

class Matrix{
public:
    int verticesCount = 0;
    int** matrix = nullptr;

    void initialize(int size);
    void insert(int row, int column, int data);                    //funkja dodaje element n koniec tablicy
    int getSize();
    int getValue(int row, int column);

    ~Matrix(){
        for(int i = 0; i < verticesCount; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
        std::cout <<"Destructor \n";
    }
};

#endif //UNTITLED_DYNAMICMATRIX_H
