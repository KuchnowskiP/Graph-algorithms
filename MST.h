//
// Created by Piotr Kuchnowski on 5/27/2023.
//

#ifndef UNTITLED3_MST_H
#define UNTITLED3_MST_H

#include "TimeCounter.h"
#include "ReadNGenerate.h"
#include "PriorityQueue.h"

/*Class implements Prim's and Kruskal's algorithms*/

class MST {
    struct Edge{
        int start, end, weight;
    };
    TimeCounter timeCounter;
    ReadNGenerate generator;

    AdjacencyLists adjacencyLists;
    Matrix matrix;

    int vertexCount = 0;
    int edgeCount = 0;
    int mstSize = 0;
    Edge* mst = new Edge[0];

    PriorityQueue priorityQueue;

    int* kruskalsArray = new int[0];

    void primsAlgorithmForLists();
    void primsAlgorithmForMatrix();
    static void mergeSortEdges(Edge* arr, int low, int high);
    static void merge(Edge* arr, int l, int m, int r);
    void makeSet();
    int findSet(int x);
    void unionTrees(int x, int y);
    void kruskalsAlgorithmForLists();
    void kruskalsAlgorithmForMatrix();
    void pushToMST(int start, int end, int weight);
    void printMST();
    void print();
    void testProcedure();
public:
    void displayMSTMenu();

    ~MST(){
        delete[] mst;
        delete[] kruskalsArray;
    }
};


#endif //UNTITLED3_MST_H
