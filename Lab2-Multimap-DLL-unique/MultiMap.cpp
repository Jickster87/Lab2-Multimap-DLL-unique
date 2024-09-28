#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
    head = tail = nullptr;
    totalElems = 0;
}


void MultiMap::add(TKey c, TValue v) {
    Node * nomad = head;
    while (nomad != nullptr) {
        if (nomad->key == c) {
            nomad->values.push_back(v);
            totalElems++;
            return;
        }
        nomad = nomad->next;
    }
    std::vector<TValue> vals = {v};
    Node * newNode = new Node(c, vals);
    newNode->next = head;
    newNode->prev = nullptr;
    //check if head
    if (head != nullptr) {
        head->prev = newNode;
    }
    //assign head as new node
    head = newNode;
    //check if new node is also (single elem in list)
    if (tail == nullptr) {
        tail = newNode;
    }
    totalElems++;
}


bool MultiMap::remove(TKey c, TValue v) {
    if (head == nullptr) {
        return false;
    }
    
    Node * nomad = head;
    //search for key
    while (nomad != nullptr) {
        if (nomad->key == c) {
            //key found, search for value in vector array
            for (int i=0; i < nomad->values.size(); i++) {
                //value found at index *+i in array
                if (nomad->values[i] == v) {
                    nomad->values.erase(nomad->values.begin()+i);
                    //value deleted from vector
                    //now check if it was the only value in array
                    if (nomad->values.empty()) {
                        //manage head, tail, in between cases of removal
                        //head
                        if (nomad == head) {
                            head = head->next;
                            if (head != nullptr) {
                                head->prev = nullptr;
                            }
                        }
                        //tail
                        else if (nomad == tail) {
                            tail = tail->prev;
                            if (tail != nullptr && nomad->next == nullptr) {
                                if (tail != nullptr) {
                                    tail->next = nullptr;
                                }
                            }
                        }
                        //inbetween
                        else {
                            if (nomad->next != nullptr) {
                                nomad->next->prev = nomad->prev;
                            }
                            if (nomad->prev != nullptr) {
                                nomad->prev->next = nomad->next;
                            }
                        }
                        delete nomad;
                    }
                    totalElems--;
                    return true;
                }
            }
        }
        nomad = nomad->next;
    }
	return  false;
}


vector<TValue> MultiMap::search(TKey c) const {
    Node * nomad = head;
    while (nomad != nullptr) {
        if (nomad->key == c) {
            return nomad->values;
        }
        nomad = nomad->next;
    }
	return vector<TValue>();
}


int MultiMap::size() const {
    return totalElems;
}


bool MultiMap::isEmpty() const {
    return totalElems == 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
    while (head != nullptr) {
        Node * temp = head;
        head = head->next;
        delete temp;
    }
}

