//
// Created by Piotr Kuchnowski on 18.03.2023.
//

#ifndef UNTITLED_DLNEIGHBOURLIST_H
#define UNTITLED_DLNEIGHBOURLIST_H



class DLNeighbourList {
public:
    struct ListNode
    {
        int data;                                   //list item value
        int weight;                                 //edge weight
        ListNode* next;                             //pointer to the next list node
        ListNode* prev;                             //pointer to the previous list's node
        ListNode(int data, ListNode* next, ListNode* prev, int weight){ //ListNode constructor
            this->data = data;
            this->next = next;
            this->prev = prev;
            this->weight = weight;
        }
    };

    ~DLNeighbourList(){
        deleteList();
    }

private:
    ListNode* headPointer = nullptr;                //pointer to the head of list
    ListNode* tailPointer = nullptr;                //pointer to the tail of list
    int size = 0;                                   //variable stores the size of list

public:
    void pushBack(int data, int weight);            //function that adds a new item to the end of the list
    void deleteList();                              //function that deletes entire list
    ListNode* getHead();                            //function that returns the head node

};


#endif //UNTITLED_DLNEIGHBOURLIST_H
