//
// Created by Piotr Kuchnowski on 5/27/2023.
//

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "MST.h"
#include <climits>

void MST::primsAlgorithmForLists() {
    priorityQueue.clear();
    mstSize = 0;
    delete[] mst;
    mst = new Edge[mstSize];
    int currentVertex;
    priorityQueue.initialize(vertexCount);
    for(int i = adjacencyLists.getSize() - 1; i >= 0; i--){
        if(i == 0) {
            priorityQueue.push(i, 0);
        }else{
            priorityQueue.push(i, INT_MAX);
        }
    }
    DLNeighbourList::ListNode* currentNListNode;
    while(!priorityQueue.empty()){
        if(priorityQueue.getHead()->getKey() != 0){
            pushToMST(priorityQueue.getHead()->getData(), priorityQueue.getHead()->getConnection(), priorityQueue.getHead()->getKey());
        }
        currentVertex = priorityQueue.extractFirst();
        currentNListNode = adjacencyLists.getList(currentVertex).getHead();
        while(currentNListNode != nullptr){
            if(priorityQueue.getNode(currentNListNode->data) != nullptr){
                if(currentNListNode->weight < priorityQueue.getNode(currentNListNode->data)->getKey()){
                    priorityQueue.deleteNode(priorityQueue.getNode(currentNListNode->data));
                    priorityQueue.push(currentNListNode->data, currentNListNode->weight);
                    priorityQueue.getNode(currentNListNode->data)->setConnection(currentVertex);
                }
            }
            currentNListNode = currentNListNode->next;
        }
    }
}

void MST::primsAlgorithmForMatrix() {
    priorityQueue.clear();
    mstSize = 0;
    delete[] mst;
    mst = new Edge[mstSize];
    int currentVertex;
    priorityQueue.initialize(vertexCount);
    for(int i = adjacencyLists.getSize() - 1; i >= 0; i--){
        if(i == 0) {
            priorityQueue.push(i, 0);
        }else{
            priorityQueue.push(i, INT_MAX);
        }
    }
    while(!priorityQueue.empty()){
        if(priorityQueue.getHead()->getKey() != 0){
            pushToMST(priorityQueue.getHead()->getData(), priorityQueue.getHead()->getConnection(), priorityQueue.getHead()->getKey());
        }
        currentVertex = priorityQueue.extractFirst();
        for(int i = 0; i < vertexCount; i++) {
            if(matrix.getValue(currentVertex,i) != INT_MAX) {
                if (priorityQueue.getNode(i) != nullptr) {
                    if (matrix.getValue(currentVertex,i) < priorityQueue.getNode(i)->getKey()) {
                        priorityQueue.deleteNode(priorityQueue.getNode(i));
                        priorityQueue.push(i, matrix.getValue(currentVertex,i));
                        priorityQueue.getNode(i)->setConnection(currentVertex);
                    }
                }
            }
        }
    }
}

void MST::makeSet() {
    for(int i = 0; i < vertexCount; i++){
        kruskalsArray[i] = i;
    }
}

int MST::findSet(int x) {
    return kruskalsArray[x];
}

void MST::unionTrees(int x, int y) {
    int previousGroup = kruskalsArray[y];
    for(int i = 0; i < vertexCount; i++){
        if(kruskalsArray[i] == previousGroup){
            kruskalsArray[i] = kruskalsArray[x];
        }
    }
}

void MST::kruskalsAlgorithmForLists() {
    mstSize = 0;
    delete[] mst;
    delete[] kruskalsArray;
    mst = new Edge[mstSize];
    kruskalsArray = new int[vertexCount];
    Edge* sortedEdges = new Edge[edgeCount];
    int edgeIterator = 0;
    makeSet();
    for(int i = 0; i < vertexCount; i++){
        DLNeighbourList::ListNode* currentNListNode = adjacencyLists.getList(i).getHead();
        while(currentNListNode != nullptr){
            if(currentNListNode->data > i) {
                sortedEdges[edgeIterator] = {i, currentNListNode->data, currentNListNode->weight};
                edgeIterator++;
            }
            currentNListNode = currentNListNode->next;
        }
    }

    mergeSortEdges(sortedEdges,0,edgeCount-1);

    for(int i = 0; i < edgeCount-1; i++){
        Edge edge = sortedEdges[i];
        if(findSet(edge.start) != findSet(edge.end)){
            pushToMST(edge.start, edge.end, edge.weight);
            unionTrees(edge.start,edge.end);
            if(mstSize == vertexCount - 1){
                break;
            }
        }
    }
    delete[] sortedEdges;
}

void MST::kruskalsAlgorithmForMatrix() {
    mstSize = 0;
    delete[] mst;
    delete[] kruskalsArray;
    mst = new Edge[mstSize];
    kruskalsArray = new int[vertexCount];
    Edge* sortedEdges = new Edge[edgeCount];
    int edgeIterator = 0;
    makeSet();
    for(int i = 0; i < vertexCount; i++){
        for(int j = i+1; j < vertexCount; j++){
            if(matrix.getValue(i,j) != INT_MAX) {
                sortedEdges[edgeIterator] = {i, j, matrix.getValue(i,j)};
                edgeIterator++;
            }
        }
    }

    mergeSortEdges(sortedEdges,0,edgeCount-1);

    for(int i = 0; i < edgeCount-1; i++){
        Edge edge = sortedEdges[i];
        if(findSet(edge.start) != findSet(edge.end)){
            pushToMST(edge.start, edge.end, edge.weight);
            unionTrees(edge.start,edge.end);
            if(mstSize == vertexCount - 1){
                break;
            }
        }
    }
    delete[] sortedEdges;
}

void MST::print() {
    std::cout << "===============Matrix===============" << std::endl << std::endl;
    if(matrix.getSize() == 0)
    {
        std::cout << "Array is empty!" << std::endl;
    }
    std::cout << "  ";
    for(int i = 0; i < matrix.getSize(); i++){
        std::cout << "\t" << i;
    }
    std::cout << std::endl;
    for(int i = 0; i < matrix.getSize(); i++)
    {
        std::cout << i << ": ";
        for(int j = 0; j < matrix.getSize(); j++) {
            if(matrix.getValue(i,j) == INT_MAX){
                std::cout << "\t" << "|" << "-" << "|";
            }else {
                std::cout << "\t" << "|" << matrix.getValue(i,j) << "|";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "===============ARRAY of LISTS===============" << std::endl << std::endl;
    DLNeighbourList currentList;
    DLNeighbourList::ListNode* currentListNode;
    int howManyEdges = 0;
    for(int i = 0; i < adjacencyLists.getSize(); i++){
        currentList = adjacencyLists.getList(i);
        currentListNode = currentList.getHead();
        std::cout << "Vertex: " << i << std::endl;
        std::cout << "Neighbours: ";
        while(currentListNode != nullptr){
            std::cout << "(" << currentListNode->data << "," << currentListNode->weight << ") ";
            if(currentListNode->data > i){
                howManyEdges++;
            }
            currentListNode = currentListNode->next;
        }
        std::cout << std::endl;
    }
    std::cout << "Edges : " << howManyEdges << std::endl;
    std::cout << "Press any key to continue\n";
    system("PAUSE");
}

void MST::pushToMST(int start, int end, int weight) {
    mstSize++;
    Edge* temp = new Edge[mstSize];

    for(int i = 0; i < mstSize - 1; i++){
        temp[i] = mst[i];
    }

    temp[mstSize-1] = {start,end,weight};
    delete[] mst;
    mst = temp;
}

void MST::printMST() {
    std::cout << "Edge" << std::setw(4) << " " << "Weight" << std::endl;
    int mstSumWeight = 0, mstSum = 0;
    for(int i = 0; i < mstSize; i++){
        std::cout << "(" << mst[i].start << "," << mst[i].end << ")" << std::setw(3) << " " << mst[i].weight << std::endl;
        mstSumWeight += mst[i].weight;
        mstSum++;
    }
    std::cout << std::endl << "MST = " << mstSumWeight << std::endl;
    std::cout << std::endl << "Edges = " << mstSum << std::endl;
    std::cout << "Press any key to continue\n";
    system("PAUSE");

}

void MST::displayMSTMenu() {
    char choice = '1';
    long long int start;
    int percentage;
    std::string filename;
    while (choice != '0') {
        std::cout << "======MST Menu======" << "\n";
        std::cout << "1. Load graph from file" << "\n";
        std::cout << "2. Generate random graph" << "\n";
        std::cout << "3. Print" << "\n";
        std::cout << "4. MST Prim's Algorithm (List)" << "\n";
        std::cout << "5. MST Prim's Algorithm (Matrix)" << "\n";
        std::cout << "6. MST Kruskal's Algorithm (List)" << "\n";
        std::cout << "7. MST Kruskal's Algorithm (Matrix)" << "\n";
        std::cout << "8. Test" << "\n";
        std::cout << "0. Exit" << std::endl;
        std::cin >> choice;
        switch (choice) {
            case '0': {
                break;
            }
            case '1': {
                std::cout << "Insert file name: " << std::endl;
                std::cin >> filename;
                generator.readFileForMST(adjacencyLists, matrix, vertexCount, edgeCount, filename);
                break;
            }
            case '2': {
                std::cout << "Insert the number of vertices: ";
                generator.insertCinSafeCheck(vertexCount);
                std::cout << "Insert graph density (in %): ";
                generator.insertCinSafeCheck(percentage);
                timeCounter.startTimer(start);
                generator.generateRandomForMST(adjacencyLists, matrix, vertexCount, edgeCount, percentage);
                timeCounter.getTime(start);
                break;
            }
            case '3': {
                print();
                break;
            }
            case '4': {
                timeCounter.startTimer(start);
                primsAlgorithmForLists();
                timeCounter.getTime(start);
                printMST();
                break;
            }
            case '5': {
                timeCounter.startTimer(start);
                primsAlgorithmForMatrix();
                timeCounter.getTime(start);
                printMST();
                break;
            }
            case '6': {
                timeCounter.startTimer(start);
                kruskalsAlgorithmForLists();
                timeCounter.getTime(start);
                printMST();
                break;
            }
            case '7': {
                timeCounter.startTimer(start);
                kruskalsAlgorithmForMatrix();
                timeCounter.getTime(start);
                printMST();
                break;
            }
            case '8':{
                testProcedure();
                break;
            }
            default: {
                std::cout << "Wrong input" << std::endl;
                system("PAUSE");
                break;
            }
        }
        system("CLS");
    }
}

void MST::mergeSortEdges(MST::Edge *arr, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSortEdges(arr, low, mid);
        mergeSortEdges(arr , mid + 1, high);
        merge(arr, low, mid, high);
    }
}


void MST::merge(MST::Edge *arr, int low, int mid, int high) {
    int mergedSize = high - low + 1;
    Edge *temp = new Edge[mergedSize];
    int mergePos = 0;
    int leftPos = low;
    int rightPos = mid + 1;

    while (leftPos <= mid && rightPos <= high)
    {
        if (arr[leftPos].weight < arr[rightPos].weight)
        {
            temp[mergePos++] = arr[leftPos++];
        }
        else
        {
            temp[mergePos++] = arr[rightPos++];
        }
    }

    while (leftPos <= mid)
    {
        temp[mergePos++] = arr[leftPos++];
    }

    while (rightPos <= high)
    {
        temp[mergePos++] = arr[rightPos++];
    }

    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        arr[low + mergePos] = temp[mergePos];
    }

    delete[] temp;
}
/*The test procedure consists in generating random graphs with positive edge weights and given density.
 * We execute all algorithms and record their execution time. Then we take the arithmetic mean. */

void MST::testProcedure() {
    int percentages[4] = {25,50,75,99};
    int amounts[5] = {10,100,1000,2500,5000};
    long long int start, elapsed, elapsedSumPrimList = 0, elapsedSumPrimMatrix = 0, elapsedSumKruskalList = 0, elapsedSumKruskalMatrix = 0;
    std::ofstream toFile;
    toFile.open("resultsMSTPOP.txt");

    toFile << "\t" << "PrimList" << "\t" << "PrimMatrix" << "\t" << "KruskalList" << "\t" << "KruskalMatrix" << "\n";
    for(int i = 0; i < 3; i++){
        toFile << amounts[i] << "\n";
        for(int j = 0; j < 4; j++){
            std::cout << "vertices: " << amounts[i] << " percentage: " << percentages[j] << "\n";
            toFile << percentages[j] << "\t";
            for(int k = 0; k < 100; k++) {
                std::cout << k << "\n";
                vertexCount = amounts[i];
                generator.generateRandomForMST(adjacencyLists, matrix, vertexCount, edgeCount, percentages[j]);
                timeCounter.startTimer(start);
                primsAlgorithmForLists();
                elapsed = timeCounter.returnTime(start);
                elapsedSumPrimList += elapsed;

                timeCounter.startTimer(start);
                primsAlgorithmForMatrix();
                elapsed = timeCounter.returnTime(start);
                elapsedSumPrimMatrix += elapsed;

                timeCounter.startTimer(start);
                kruskalsAlgorithmForLists();
                elapsed = timeCounter.returnTime(start);
                elapsedSumKruskalList += elapsed;

                timeCounter.startTimer(start);
                kruskalsAlgorithmForMatrix();
                elapsed = timeCounter.returnTime(start);
                elapsedSumKruskalMatrix += elapsed;
            }
            elapsedSumPrimList /= 100;
            elapsedSumPrimMatrix /= 100;
            elapsedSumKruskalList /= 100;
            elapsedSumKruskalMatrix /= 100;
            toFile << elapsedSumPrimList << "\t" << elapsedSumPrimMatrix << "\t" << elapsedSumKruskalList << "\t" << elapsedSumKruskalMatrix << "\n";
        }
    }
    toFile.close();
}
