//
// Created by kuchn on 18.03.2023.
//

#ifndef UNTITLED_DLNEIGHBOURLIST_H
#define UNTITLED_DLNEIGHBOURLIST_H



class DLNeighbourList {
public:
    struct ListNode
    {
        int data;                                   //wartosc elementu listy
        int weight;                                 //waga krawedzi
        ListNode* next;                             //wskaznik na nastepny wezeł
        ListNode* prev;                             //wskaznik na wezel poprzedzajacy
        ListNode(int data, ListNode* next, ListNode* prev, int weight){
            this->data = data;
            this->next = next;
            this->prev = prev;
            this->weight = weight;
        }
    };

private:
    ListNode* headPointer = nullptr;                //wskaznik na glowe
    ListNode* tailPointer = nullptr;                //wskaznik na ogon
    int size = 0;                                   //zmienna przechowujaca rozmiar listy

public:
    void pushBack(int data, int weight);            //funkcja dodajaca element na koniec listy
    void deleteList();
    ListNode* getHead();

};


#endif //UNTITLED_DLNEIGHBOURLIST_H
