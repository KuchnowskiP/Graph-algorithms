//
// Created by kuchn on 18.03.2023.
//

#include <cstdlib>
#include "DLNeighbourList.h"

void DLNeighbourList::pushBack(int data, int weight) {
ListNode* node = new ListNode(data, nullptr, tailPointer, weight);

    if (headPointer == nullptr)                 //checking if list is empty, if so, new node is also new head and tail
    {
        headPointer = node;
        tailPointer = node;
        size++;
        return;
    }

    tailPointer->next = node;
    tailPointer = node;

    size++;
}

void DLNeighbourList::deleteList() {
    ListNode* current = headPointer;
    ListNode* next;

    while(current != nullptr){
        next = current->next;
        delete current;
        current = next;
    }

    headPointer = nullptr;
    tailPointer = nullptr;
}

DLNeighbourList::ListNode *DLNeighbourList::getHead() {
    return headPointer;
}
