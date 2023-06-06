//
// Created by Piotr Kuchnowski on 5/27/2023.
//

#ifndef UNTITLED3_SHORTESTPATH_H
#define UNTITLED3_SHORTESTPATH_H


#include "TimeCounter.h"
#include "ReadNGenerate.h"
#include "PriorityQueue.h"

class ShortestPath {
    struct Edge{
        int start, end, weight;
        bool considered = false;
    };

    TimeCounter timeCounter;
    ReadNGenerate generator;

    AdjacencyLists adjacencyLists;
    Matrix matrix;

    int vertexCount = 0;
    int edgeCount = 0;
    int startingVertex = 0;

    Edge* shortestPathArray = nullptr;
    int* path;
    int pathDistance = 0;

    PriorityQueue priorityQueue;

    void dijkstrasAlgorithmForLists();
    void dijkstrasAlgorithmForMatrix();
    void bellmanFordAlgorithmForLists();
    void bellmanFordAlgorithmForMatrix();
    void changeSP(int start, int end, int weight);
    void vertexConsidered(int vertex);
    void print();
    void printSP();
    void testProcedure();
public:
    void displaySPMenu();

    ~ShortestPath(){
        delete[] shortestPathArray;
        delete[] path;
    }


};


#endif //UNTITLED3_SHORTESTPATH_H
