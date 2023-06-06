//
// Created by Piotr Kuchnowski on 5/27/2023.
//

#include "AdjacencyLists.h"

void AdjacencyLists::initialize(int size) {
    for(int i = 0; i < verticesCount; i++){
        neighbourLists[i].deleteList();
    }
    delete[] neighbourLists;
    verticesCount = size;
    neighbourLists = new DLNeighbourList[verticesCount];
}

void AdjacencyLists::insert(int list, int data, int weight) {
    neighbourLists[list].pushBack(data,weight);
}

int AdjacencyLists::getSize() const{
    return verticesCount;
}

DLNeighbourList AdjacencyLists::getList(int i) const{
    return neighbourLists[i];
}
