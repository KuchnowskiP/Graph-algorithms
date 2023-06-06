//
// Created by Piotr Kuchnowski on 5/28/2023.
//

#ifndef UNTITLED3_PRIORITYQUEUE_H
#define UNTITLED3_PRIORITYQUEUE_H


class PriorityQueue {
    struct QueueNode{
        int data = -1;
        int key = -1;
        int connection = -1;
        QueueNode* next = nullptr;
        QueueNode* prev = nullptr;
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
        int getKey() const;
        int getData() const;
        int getConnection() const;
        void setConnection(int connection);
    };

    int queueSize = 0;
    QueueNode** quickAccessArray = nullptr;

    QueueNode* headPointer = nullptr;
public:
    void initialize(int size);
    void updateQuickAccessArray(QueueNode* node, int data);
    void push(int data, int key);
    void pushEdge(int data, int key, int connection);
    int extractFirst();
    void extractFirstEdge(int &start, int &end, int &key);
    void deleteNode(QueueNode* node);
    QueueNode* getNode(int data);
    QueueNode* getHead();
    void clear();
    bool empty() const;
};


#endif //UNTITLED3_PRIORITYQUEUE_H
