//
// Created by Piotr Kuchnowski on 5/27/2023.
//

#ifndef UNTITLED3_ADJACENCYLISTS_H
#define UNTITLED3_ADJACENCYLISTS_H


#include "DLNeighbourList.h"

class AdjacencyLists {
    int verticesCount = 0;
    DLNeighbourList* neighbourLists = new DLNeighbourList[verticesCount];

public:
    void initialize(int size);
    void insert(int list, int data, int weight);
    int getSize() const;
    DLNeighbourList getList(int i) const;

    ~AdjacencyLists(){
        for(int i = 0; i < verticesCount; i++){
            neighbourLists[i].deleteList();
        }
        delete[] neighbourLists;
    }
};


#endif //UNTITLED3_ADJACENCYLISTS_H

#pragma clang diagnostic pop