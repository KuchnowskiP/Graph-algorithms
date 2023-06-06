//
// Created by Piotr Kuchnowski on 5/28/2023.
//

#ifndef UNTITLED3_PRIORITYQUEUE_H
#define UNTITLED3_PRIORITYQUEUE_H

/*This class is an implementation of a priority queue used in algorithms for sorting edges by weights ascending */

class PriorityQueue {
    struct QueueNode{
        int data = -1;                          //queue item value
        int key = -1;                           //the value by which the queue is sorted
        int connection = -1;                    //for Prims algorithm, the vertex to which the vertex represented by data is connected
        QueueNode* next = nullptr;              //pointer to the next queue node
        QueueNode* prev = nullptr;              //pointer to the previous queue node
        QueueNode(int data, int key){
            this->data = data;
            this->key = key;
        }
        QueueNode(int data, int key, int connection){
            this->data = data;
            this->key = key;
            this->connection = connection;
        }
        QueueNode() = default;
        int getKey() const;                     //function that returns node's key
        int getData() const;                    //function that returns node's data
        int getConnection() const;              //function that returns node's connection
        void setConnection(int connection);     //function that sets node's connection
    };

    int queueSize = 0;
    QueueNode** quickAccessArray = nullptr;     //array of pointers on queue nodes for faster access

    QueueNode* headPointer = nullptr;
public:
    void initialize(int size);                              //function that initializes queue, freeing up memory occupied by previous queue
    void updateQuickAccessArray(QueueNode* node, int data); //function updates quick access array
    void push(int data, int key);                           //function inserts the node into the appropriate place by sorting by key
    void pushEdge(int data, int key, int connection);       //function inserts the node into the appropriate place by sorting by key
    int extractFirst();                                     //function pops first node and returns its data
    void extractFirstEdge(int &start, int &end, int &key);  //function pops first node and assigns its values by references
    void deleteNode(QueueNode* node);                       //function deletes given node
    QueueNode* getNode(int data);                           //function returns node with given data
    QueueNode* getHead();                                   //function returns first node
    void clear();                                           //function that clears entire queue
    bool empty() const;                                     //function returns whether queue is empty
};


#endif //UNTITLED3_PRIORITYQUEUE_H
