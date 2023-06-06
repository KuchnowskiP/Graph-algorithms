//
// Created by Piotr Kuchnowski on 5/27/2023.
//

#include <string>
#include <iostream>
#include <iomanip>
#include "ShortestPath.h"
#include <climits>
#include <fstream>

void ShortestPath::dijkstrasAlgorithmForLists() {
    priorityQueue.clear();
    priorityQueue.initialize(vertexCount);
    shortestPathArray = new Edge[vertexCount];
    for(int i = 0; i < vertexCount; i++){
        shortestPathArray[i].weight = INT_MAX;
    }

    bool negativeDetected = false;
    int consideredVertices = 0;

    priorityQueue.push(startingVertex,0);
    changeSP(startingVertex, startingVertex, 0);

    while(true){
        Edge currentNode{};
        priorityQueue.extractFirstEdge(currentNode.start, currentNode.end, currentNode.weight);
        DLNeighbourList::ListNode* currentNListNode = adjacencyLists.getList(currentNode.start).getHead();
        while(currentNListNode != nullptr){
            if(!shortestPathArray[currentNListNode->data].considered && shortestPathArray[currentNListNode->data].weight > shortestPathArray[currentNode.start].weight + currentNListNode->weight) {
                if(priorityQueue.getNode(currentNListNode->data) == nullptr) {
                    priorityQueue.pushEdge(currentNListNode->data, currentNode.weight + currentNListNode->weight,currentNode.start);
                }
                if(currentNListNode->weight < 0){
                    negativeDetected = true;
                }
                changeSP(currentNode.start,currentNListNode->data,shortestPathArray[currentNode.start].weight + currentNListNode->weight);
            }
            currentNListNode = currentNListNode->next;
        }
        vertexConsidered(currentNode.start);
        consideredVertices++;
        if(consideredVertices == vertexCount){
            break;
        }
    }
    if(negativeDetected){
        std::cout << "NEGATIVE EDGE! Results may not be accurate!" << std::endl;
    }
}

void ShortestPath::dijkstrasAlgorithmForMatrix() {
    priorityQueue.clear();
    priorityQueue.initialize(vertexCount);
    shortestPathArray = new Edge[vertexCount];
    for(int i = 0; i < vertexCount; i++){
        shortestPathArray[i].weight = INT_MAX;
    }

    bool negativeDetected = false;
    int consideredVertices = 0;

    priorityQueue.push(startingVertex,0);
    changeSP(startingVertex, startingVertex, 0);

    while(true){
        Edge currentNode{};
        priorityQueue.extractFirstEdge(currentNode.start, currentNode.end, currentNode.weight);
        for(int i = 0; i < vertexCount; i++){
            if(matrix.getValue(currentNode.start,i) != INT_MAX) {
                if (!shortestPathArray[i].considered && shortestPathArray[i].weight >
                                                        shortestPathArray[currentNode.start].weight +
                                                        matrix.getValue(currentNode.start, i)) {
                    if (priorityQueue.getNode(i) == nullptr) {
                        priorityQueue.pushEdge(i, currentNode.weight + matrix.getValue(currentNode.start, i),currentNode.start);
                    }
                    if (matrix.getValue(currentNode.start, i) < 0) {
                        negativeDetected = true;
                    }
                    changeSP(currentNode.start, i,shortestPathArray[currentNode.start].weight + matrix.getValue(currentNode.start, i));
                }
            }
        }
        vertexConsidered(currentNode.start);
        consideredVertices++;
        if(consideredVertices == vertexCount){
            break;
        }
    }
    if(negativeDetected){
        std::cout << "NEGATIVE EDGE! Results may not be accurate!" << std::endl;
    }
}

void ShortestPath::bellmanFordAlgorithmForLists() {
    bool change;
    shortestPathArray = new Edge[vertexCount];
    for(int i = 0; i < vertexCount; i++){
        changeSP(-1, i, INT_MAX);
    }
    shortestPathArray[startingVertex].weight = 0;
    DLNeighbourList::ListNode* currentNListNode;
    for(int i = 1; i < vertexCount; i++){
        change = false;
        for(int u = 0; u < vertexCount; u++){
            if(shortestPathArray[u].weight == INT_MAX){
                continue;
            }
            currentNListNode = adjacencyLists.getList(u).getHead();
            while(currentNListNode != nullptr){
                if(shortestPathArray[currentNListNode->data].weight > shortestPathArray[u].weight + currentNListNode->weight){
                    change = true;
                    shortestPathArray[currentNListNode->data].weight = shortestPathArray[u].weight + currentNListNode->weight;
                    shortestPathArray[currentNListNode->data].start = u;
                }
                currentNListNode = currentNListNode->next;
            }
        }
        if(!change){
            break;
        }
    }

    bool negative = false;
    for(int u = 0; u < vertexCount; u++){
        currentNListNode = adjacencyLists.getList(u).getHead();
        while(currentNListNode != nullptr) {
            if (shortestPathArray[currentNListNode->data].weight > shortestPathArray[u].weight + currentNListNode->weight) {
                std::cout << "NEGATIVE CYCLE!" << std::endl;
                system("PAUSE");
                negative = true;
                break;
            }
            currentNListNode = currentNListNode->next;
        }
        if(negative){
            break;
        }

    }
}

void ShortestPath::bellmanFordAlgorithmForMatrix() {
    bool change;
    shortestPathArray = new Edge[vertexCount];
    for(int i = 0; i < vertexCount; i++){
        changeSP(0, i, INT_MAX);
    }
    shortestPathArray[startingVertex].weight = 0;
    for(int i = 1; i < vertexCount; i++){
        change = false;
        for(int u = 0; u < vertexCount; u++){
            if(shortestPathArray[u].weight == INT_MAX){
                continue;
            }
            for(int v = 0; v < vertexCount; v++){
                if(matrix.getValue(u,v) != INT_MAX){
                    if(shortestPathArray[v].weight > shortestPathArray[u].weight + matrix.getValue(u,v)){
                        change = true;
                        shortestPathArray[v].weight = shortestPathArray[u].weight + matrix.getValue(u,v);
                        shortestPathArray[v].start = u;
                    }
                }
            }
        }
        if(!change){
            break;
        }
    }
    bool negative = false;
    for(int u = 0; u < vertexCount; u++){
        for(int v = 0; v < vertexCount; v++){
            if(matrix.getValue(u,v) != INT_MAX) {
                if (shortestPathArray[v].weight > shortestPathArray[u].weight + matrix.getValue(u,v)) {
                    std::cout << "NEGATIVE CYCLE!." << std::endl;
                    system("PAUSE");
                    negative = true;
                    break;
                }
            }
        }
        if(negative){
            break;
        }
    }
}

void ShortestPath::changeSP(int start, int end, int weight) {
    shortestPathArray[end].start = start;
    shortestPathArray[end].end = end;
    shortestPathArray[end].weight = weight;
}

void ShortestPath::vertexConsidered(int vertex) {
    shortestPathArray[vertex].considered = true;
}

void ShortestPath::print() {
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
            howManyEdges++;
            currentListNode = currentListNode->next;
        }
        std::cout << std::endl;
    }
    std::cout << "Edges : " << howManyEdges << std::endl;
    system("PAUSE");
}

void ShortestPath::printSP() {
    std::cout << "START: " << std::setw(3) << startingVertex << std::endl;
    std::cout << "Edge" << std::setw(3) << " Dist" << std::setw(3) << " Path" << std::endl;
    for(int i = 0; i < vertexCount; i++){
        int currentVertex = i;
        path = new int[1];
        path[0] = currentVertex;
        pathDistance = 0;
        while(currentVertex != startingVertex){
            currentVertex = shortestPathArray[currentVertex].start;
            int *newPath = new int[pathDistance + 2];
            for(int j = pathDistance + 1; j > 0; j--){
                newPath[j] = path[j - 1];
            }
            newPath[0] = currentVertex;
            path = newPath;
            pathDistance++;
        }
        std::cout << path[pathDistance] << std::setw(3)  << '|' << std::setw(3) << shortestPathArray[path[pathDistance]].weight <<std::setw(3)  << '|';
        for(int j = 0; j <= pathDistance; j++){
            std::cout << "\t" << path[j];
        }
        std::cout << std::endl;
    }
    delete[] shortestPathArray;
    system("PAUSE");
}

void ShortestPath::displaySPMenu() {
    char choice = '1';
    long long int start;
    int percentage;
    std::string filename;
    while (choice != '0') {
        std::cout << "======Shortest Path Menu======" << "\n";
        std::cout << "1. Load graph" << "\n";
        std::cout << "2. Generate random graph" << "\n";
        std::cout << "3. Print" << "\n";
        std::cout << "4. Djikstra's Algorithm (List)" << "\n";
        std::cout << "5. Djikstra's Algorithm (Matrix)" << "\n";
        std::cout << "6. Bellman-Ford Algorithm (List)" << "\n";
        std::cout << "7. Bellman-Ford Algorithm (Matrix)" << "\n";
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
                generator.readFileForSP(adjacencyLists, matrix, vertexCount, edgeCount, filename, startingVertex);
                break;
            }
            case '2': {
                std::cout << "Insert the number of vertices: ";
                generator.insertCinSafeCheck(vertexCount);
                std::cout << "Insert graph density (in %): ";
                generator.insertCinSafeCheck(percentage);
                timeCounter.startTimer(start);
                generator.generateRandomForSP(adjacencyLists, matrix, vertexCount, edgeCount, percentage, startingVertex);
                timeCounter.getTime(start);
                break;
            }
            case '3': {
                print();
                break;
            }
            case '4': {
                timeCounter.startTimer(start);
                dijkstrasAlgorithmForLists();
                timeCounter.getTime(start);
                printSP();
                break;
            }
            case '5': {
                timeCounter.startTimer(start);
                dijkstrasAlgorithmForMatrix();
                timeCounter.getTime(start);
                printSP();
                break;
            }
            case '6': {
                timeCounter.startTimer(start);
                bellmanFordAlgorithmForLists();
                timeCounter.getTime(start);
                printSP();
                break;
            }
            case '7': {
                timeCounter.startTimer(start);
                bellmanFordAlgorithmForMatrix();
                timeCounter.getTime(start);
                printSP();
                break;
            }
            case '8': {
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

void ShortestPath::testProcedure() {
    int percentages[4] = {25,50,75,99};
    int amounts[5] = {10,100,1000,2500,5000};
    long long int start, elapsed, elapsedSumDjikstraList = 0, elapsedSumBellmanList = 0, elapsedSumDjikstraMatrix = 0, elapsedSumBellmanMatrix = 0;
    std::ofstream toFile;
    toFile.open("resultsSPPOP.txt");

    toFile << "\t" << "DjikstraList" << "\t" << "BellmanList" << "\t" << "DjikstraMatrix" << "\t" << "BellmanMatrix" << "\n";
    for(int i = 0; i < 3; i++){
        toFile << amounts[i] << "\n";
        for(int j = 0; j < 4; j++){
            std::cout << "vertices: " << amounts[i] << " percentage: " << percentages[j] << "\n";
            toFile << percentages[j] << "\t";
            for(int k = 0; k < 100; k++) {
                std::cout << k << "\n";
                vertexCount = amounts[i];
                generator.generateRandomForSP(adjacencyLists, matrix, vertexCount, edgeCount, percentages[j],startingVertex);
                timeCounter.startTimer(start);
                dijkstrasAlgorithmForLists();
                elapsed = timeCounter.returnTime(start);
                elapsedSumDjikstraList += elapsed;

                timeCounter.startTimer(start);
                bellmanFordAlgorithmForLists();
                elapsed = timeCounter.returnTime(start);
                elapsedSumBellmanList += elapsed;

                timeCounter.startTimer(start);
                dijkstrasAlgorithmForMatrix();
                elapsed = timeCounter.returnTime(start);
                elapsedSumDjikstraMatrix += elapsed;

                timeCounter.startTimer(start);
                bellmanFordAlgorithmForMatrix();
                elapsed = timeCounter.returnTime(start);
                elapsedSumBellmanMatrix += elapsed;
            }
            elapsedSumDjikstraList /= 100;
            elapsedSumBellmanList /= 100;
            elapsedSumDjikstraMatrix /= 100;
            elapsedSumBellmanMatrix /= 100;
            toFile << elapsedSumDjikstraList << "\t" << elapsedSumBellmanList << "\t" << elapsedSumDjikstraMatrix << "\t" << elapsedSumBellmanMatrix << "\n";
        }
    }
    toFile.close();
}