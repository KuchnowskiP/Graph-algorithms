//
// Created by Piotr Kuchnowski on 30.03.2023.
//

#include "ReadNGenerate.h"
#include "AdjacencyLists.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>


void ReadNGenerate::readFileForMST(AdjacencyLists &adjacencyLists, Matrix &matrix, int& vertexCount, int& edgeCount, std::string filename) {
    int start, end, weight, skip;
    std::ifstream file;
    file.open(filename);

    if (file.is_open()) {
        file >> edgeCount;
        file >> vertexCount;

        matrix.initialize(vertexCount);
        adjacencyLists.initialize(vertexCount);

        file >> skip;
        file >> skip;

        if (file.fail()) {
            std::cout << "File error - READ SIZE" << std::endl << std::endl;
            return;
        }
        else
            for (int i = 0; i < edgeCount; i++) {
                file >> start;
                file >> end;
                file >> weight;

                adjacencyLists.insert(start, end, weight);
                adjacencyLists.insert(end, start, weight);
                matrix.insert(start, end, weight);
                matrix.insert(end,start,weight);
            }
        file.close();
    } else {
        std::cout << "File error - OPEN" << std::endl << std::endl;
        return;
    }
    std::cout << "File successfully read" << std::endl << std::endl;
}

void ReadNGenerate::readFileForSP(AdjacencyLists &adjacencyLists, Matrix &matrix, int &vertexCount, int &edgeCount, std::string filename, int &startingVertex) {
    int start, end, weight, skip;
    std::ifstream file;
    file.open(filename);

    if (file.is_open()) {
        file >> edgeCount;
        file >> vertexCount;

        matrix.initialize(vertexCount);
        adjacencyLists.initialize(vertexCount);

        file >> startingVertex;
        file >> skip;
        if (file.fail()) {
            std::cout << "File error - READ SIZE" << std::endl << std::endl;
            return;
        }
        else
            for (int i = 0; i < edgeCount; i++) {
                file >> start;
                file >> end;
                file >> weight;

                adjacencyLists.insert(start, end, weight);
                matrix.insert(start,end,weight);
            }
        file.close();
    } else {
        std::cout << "File error - OPEN" << std::endl << std::endl;
        return;
    }
    std::cout << "File successfully read" << std::endl << std::endl;
}

void ReadNGenerate::insertCinSafeCheck(int &insert) {
    std::string givenString;
    bool itsGood = false;
    while (!itsGood) {
        std::cin >> givenString;
        for (int i = 0; i < givenString.size(); i++) {
            if (givenString.at(i) < '0' || givenString.at(i) > '9') {
                std::cout << "Insert proper value!" << std::endl;
                break;
            }
            if (i == givenString.length() - 1) {
                itsGood = true;
            }
        }
    }
    insert = std::stoi(givenString);
}

void ReadNGenerate::generateRandomForMST(AdjacencyLists &adjacencyLists, Matrix &matrix, int vertexCount, int &edgeCount, int percentage) {
    std::random_device rd; // non-deterministic generator
    std::mt19937 gen(rd()); // random engine seeded with rd()
    std::uniform_int_distribution<> distWeight(1, 1000); // distribute results between
    int edgesCreated = 0, val;

    matrix.initialize(vertexCount);
    adjacencyLists.initialize(vertexCount);

    edgeCount = (0.01 * percentage) * ((vertexCount * (vertexCount - 1)) / 2);

    Edge* allPossibleEdges = new Edge[(vertexCount * vertexCount - 1) - (vertexCount - 1)];
    std::vector<int> unusedEdges((vertexCount * vertexCount - 1) - (vertexCount - 1));

    int possibleEdgeCounter = 0, weight;
    for(int i = 0; i < vertexCount; i++){
        for(int j = i + 1; j < vertexCount; j++){
            if(j != i + 1) {
                weight = distWeight(gen);
                allPossibleEdges[possibleEdgeCounter] = {i, j, weight};
                unusedEdges[possibleEdgeCounter] = 1;
                possibleEdgeCounter++;
            }else{
                val = distWeight(gen);
                matrix.insert(i,j,val);
                matrix.insert(j,i,val);
                adjacencyLists.insert(i, j, val);
                adjacencyLists.insert(j, i, val);
                edgesCreated++;
            }
        }
    }

    int start, end;

    std::discrete_distribution<> distUsed(unusedEdges.begin(), unusedEdges.end());
    for (int i = edgesCreated; i < edgeCount; i++) {
        val = distUsed(gen);
        while(unusedEdges[val] == 0){
            if(val != possibleEdgeCounter - 1){
                val++;
            }else{
                val = distUsed(gen);
            }
        }
        start = allPossibleEdges[val].start;
        end = allPossibleEdges[val].end;
        weight = allPossibleEdges[val].weight;
        unusedEdges[val] = 0;
        adjacencyLists.insert(start, end, weight);
        adjacencyLists.insert(end, start, weight);
        matrix.insert(start,end,weight);
        matrix.insert(end,start,weight);
    }

    delete[] allPossibleEdges;
}

void ReadNGenerate::generateRandomForSP(AdjacencyLists &adjacencyLists, Matrix &matrix, int vertexCount, int &edgeCount, int percentage, int &startingVertex) {
    std::random_device rd; // non-deterministic generator
    std::mt19937 gen(rd()); // random engine seeded with rd()
    std::uniform_int_distribution<> distStarting(0, vertexCount-1); // distribute results between
    startingVertex = distStarting(gen);
    std::uniform_int_distribution<> distWeight(1, 1000); // distribute results between
    int edgesCreated = 0, val;

    matrix.initialize(vertexCount);
    adjacencyLists.initialize(vertexCount);

    edgeCount = (0.01 * percentage) * (vertexCount * (vertexCount - 1));

    Edge* allPossibleEdges = new Edge[((vertexCount * vertexCount - 1) - (vertexCount - 1))*2];
    std::vector<int> unusedEdges(((vertexCount * vertexCount - 1) - (vertexCount - 1))*2);

    int possibleEdgeCounter = 0, weight;
    for(int i = 0; i < vertexCount; i++){
        for(int j = 0; j < vertexCount; j++){
            if(j != i + 1) {
                weight = distWeight(gen);
                allPossibleEdges[possibleEdgeCounter] = {i, j, weight};
                unusedEdges[possibleEdgeCounter] = 1;
                possibleEdgeCounter++;
            }else if (i != j){
                val = distWeight(gen);
                if(i < startingVertex){
                    matrix.insert(j, i, val);
                    adjacencyLists.insert(j, i, val);
                }else {
                    matrix.insert(i, j, val);
                    adjacencyLists.insert(i, j, val);
                }
                edgesCreated++;
            }
        }
    }

    int start, end;

    std::discrete_distribution<> distUsed(unusedEdges.begin(), unusedEdges.end());
    for (int i = edgesCreated; i < edgeCount; i++) {
        val = distUsed(gen);
        while(unusedEdges[val] == 0){
            if(val != possibleEdgeCounter - 1){
                val++;
            }else{
                val = distUsed(gen);
            }
        }
        start = allPossibleEdges[val].start;
        end = allPossibleEdges[val].end;
        weight = allPossibleEdges[val].weight;
        unusedEdges[val] = 0;
        adjacencyLists.insert(start, end, weight);
        matrix.insert(start,end,weight);
    }
    delete[] allPossibleEdges;
}

