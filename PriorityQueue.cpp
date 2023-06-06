//
// Created by Piotr Kuchnowski on 5/28/2023.
//

#include "PriorityQueue.h"

void PriorityQueue::initialize(int size) {
    for(int i = 0; i < queueSize; i++){
        delete quickAccessArray[i];
    }
    delete[] quickAccessArray;
    queueSize = size;
    quickAccessArray = new QueueNode* [queueSize];
    for(int i = 0; i < queueSize; i++){
        quickAccessArray[i] = nullptr;
    }
}

void PriorityQueue::updateQuickAccessArray(PriorityQueue::QueueNode *node, int data) {
    quickAccessArray[data] = node;
}

void PriorityQueue::push(int data, int key) {
    QueueNode* addedNode = new QueueNode(data,key);

    if(headPointer == nullptr){
        headPointer = addedNode;
        updateQuickAccessArray(addedNode, data);
        return;
    }

    QueueNode* currentLoopNode = headPointer;

    while(currentLoopNode->key < addedNode->key && currentLoopNode->next != nullptr){
        currentLoopNode = currentLoopNode->next;
    }

    if(currentLoopNode == headPointer) {
        if(currentLoopNode->key > addedNode->key || (currentLoopNode->key == addedNode->key && currentLoopNode->data > addedNode->data)){
            addedNode->next = currentLoopNode;
            currentLoopNode->prev = addedNode;
            headPointer = addedNode;
            updateQuickAccessArray(addedNode, data);
            return;
        }
        addedNode->next = currentLoopNode->next;
        if(addedNode->next != nullptr){
            addedNode->next->prev = addedNode;
        }
        currentLoopNode->next = addedNode;
        addedNode->prev = currentLoopNode;
        updateQuickAccessArray(addedNode, data);
        return;
    }

    if(currentLoopNode->next == nullptr && currentLoopNode->data < addedNode->data){
        addedNode->prev = currentLoopNode;
        currentLoopNode->next = addedNode;
        updateQuickAccessArray(addedNode, data);
        return;
    }

    addedNode->next = currentLoopNode;
    addedNode->prev = currentLoopNode->prev;
    currentLoopNode->prev = addedNode;
    addedNode->prev->next = addedNode;

    updateQuickAccessArray(addedNode, data);
}

void PriorityQueue::pushEdge(int data, int key, int connection) {
    QueueNode* addedNode = new QueueNode(data,key,connection);

    if(headPointer == nullptr){
        headPointer = addedNode;
        updateQuickAccessArray(addedNode, data);
        return;
    }

    QueueNode* currentLoopNode = headPointer;

    while(currentLoopNode->key < addedNode->key && currentLoopNode->next != nullptr){
        currentLoopNode = currentLoopNode->next;
    }

    if(currentLoopNode == headPointer) {
        if(currentLoopNode->key > addedNode->key || (currentLoopNode->key == addedNode->key && currentLoopNode->data > addedNode->data)){
            addedNode->next = currentLoopNode;
            currentLoopNode->prev = addedNode;
            headPointer = addedNode;
            updateQuickAccessArray(addedNode, data);
            return;
        }
        addedNode->next = currentLoopNode->next;
        if(addedNode->next != nullptr){
            addedNode->next->prev = addedNode;
        }
        currentLoopNode->next = addedNode;
        addedNode->prev = currentLoopNode;
        updateQuickAccessArray(addedNode, data);
        return;
    }

    if(currentLoopNode->next == nullptr){
        addedNode->prev = currentLoopNode;
        currentLoopNode->next = addedNode;
        updateQuickAccessArray(addedNode, data);
        return;
    }

    addedNode->next = currentLoopNode;
    addedNode->prev = currentLoopNode->prev;
    currentLoopNode->prev = addedNode;
    addedNode->prev->next = addedNode;

    updateQuickAccessArray(addedNode, data);
}

int PriorityQueue::extractFirst() {
    queueSize--;
    int toReturn = headPointer->data;
    if (headPointer->next == nullptr)           //jeżeli lista jest jednoelementowa
    {
        updateQuickAccessArray(nullptr, headPointer->data);
        delete headPointer;
        headPointer = nullptr;
        return toReturn;
    }

    QueueNode* newHead = headPointer->next;
    newHead->prev = nullptr;
    updateQuickAccessArray(nullptr, headPointer->data);
    delete headPointer;
    headPointer = newHead;
    return toReturn;
}

void PriorityQueue::extractFirstEdge(int &start, int &end, int &key) {
    queueSize--;
    start = headPointer->getData();
    end = headPointer->getConnection();
    key = headPointer->getKey();
    if (headPointer->next == nullptr)           //jeżeli lista jest jednoelementowa
    {
        updateQuickAccessArray(nullptr, headPointer->data);
        delete headPointer;
        headPointer = nullptr;
        return;
    }

    QueueNode* newHead = headPointer->next;
    newHead->prev = nullptr;
    updateQuickAccessArray(nullptr, headPointer->data);
    delete headPointer;
    headPointer = newHead;
}

void PriorityQueue::deleteNode(PriorityQueue::QueueNode *node) {
    if(node == headPointer){
        headPointer = headPointer->next;
    }
    if(node->prev != nullptr) {
        node->prev->next = node->next;
    }
    if(node->next != nullptr) {
        node->next->prev = node->prev;
    }
    delete node;
}

PriorityQueue::QueueNode *PriorityQueue::getNode(int data) {
    return quickAccessArray[data];
}

void PriorityQueue::clear() {
    while(headPointer != nullptr){
        extractFirst();
    }
    queueSize = 0;
}

bool PriorityQueue::empty() const{
    if(queueSize == 0){
        return true;
    }
    return false;
}

PriorityQueue::QueueNode *PriorityQueue::getHead() {
    return headPointer;
}

int PriorityQueue::QueueNode::getKey() const{
    return key;
}

int PriorityQueue::QueueNode::getData() const{
    return data;
}

int PriorityQueue::QueueNode::getConnection() const{
    return connection;
}

void PriorityQueue::QueueNode::setConnection(int newConnection) {
    connection = newConnection;
}
