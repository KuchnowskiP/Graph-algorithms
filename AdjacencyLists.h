//
// Created by Piotr Kuchnowski on 5/27/2023.
//

#ifndef UNTITLED3_ADJACENCYLISTS_H
#define UNTITLED3_ADJACENCYLISTS_H


#include "DLNeighbourList.h"

/*This class represents graph as an dynamic array of adjacency lists*/

class AdjacencyLists {
    int verticesCount = 0;
    DLNeighbourList* neighbourLists = new DLNeighbourList[verticesCount];

public:
    void initialize(int size);                      //function that initializes list, freeing up memory occupied by previous lists
    void insert(int list, int data, int weight);    //function that inserts neighbour to vertex's adjacency list
    int getSize() const;                            //function that returns verticesCount
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