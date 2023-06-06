//
// Created by kuchn on 30.03.2023.
//

#ifndef UNTITLED_READNGENERATE_H
#define UNTITLED_READNGENERATE_H


#include <string>
#include "Matrix.h"
#include "AdjacencyLists.h"

class ReadNGenerate {
public:

    struct Edge{
        int start, end, weight;
    };

    void insertCinSafeCheck(int &insert);                                   //A function protecting against entering not a number in a place where a number is expected
    void readFileForMST(AdjacencyLists &adjacencyLists , Matrix &matrix, int &vertexCount, int &edgeCount, std::string filename);
    void readFileForSP(AdjacencyLists &adjacencyLists , Matrix &matrix, int &vertexCount, int &edgeCount, std::string filename, int &startingVertex);
    void generateRandomForMST(AdjacencyLists &adjacencyLists , Matrix &matrix, int vertexCount, int &edgeCount, int percentage);
    void generateRandomForSP(AdjacencyLists &adjacencyLists, Matrix &matrix, int vertexCount, int &edgeCount, int percentage, int &startingVertex);
};


#endif //UNTITLED_READNGENERATE_H
