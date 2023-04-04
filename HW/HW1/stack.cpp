#include <iostream>
#include "stack.h"
using namespace std;

template <class T>
Stack<T>::Stack(){
    stackPtr = NULL;
}

template <class T>
Stack<T>::~Stack(){
    item* p1;  // p1 will point to the second top of the stack
    item* p2;  // p2 will point to the top of stack

    p1 = stackPtr;

    while (p1 != NULL)
    {
        p2 = p1;  // Set p2 to be pointing to the top of stack
        p1 = p1->prev;  /* p1->prev means stackPtr->prev, which is 
                           the second top of the stack.*/
        p2->prev = NULL;  // Discontect the top from the second top
        delete p2;
    }
}

template <class T>
void Stack<T>::Push(T value) {

    item* n = new item;
    n->value = value;

    if(stackPtr == NULL)
    {
        stackPtr = n;
        stackPtr->prev = NULL;
    }
    else
    {
        n->prev = stackPtr;
        stackPtr = n;
    }
}


template <class T>
void Stack<T>::ReadItem(item* r) {
    cout << "----------------\n";
    cout << "value: " << r->value << endl;
    cout << "----------------\n";
}

template <class T>
void Stack<T>::Pop() {

    if(stackPtr == NULL){
        cout << "There is nothing on the stack\n";
    }
    else {
        item* p = stackPtr;  // p points to the top
        ReadItem(p);
        stackPtr = stackPtr->prev; // stackPtr point to the second top,
                                   // since the first top will be deleted
        p->prev = NULL;  // Disconect the first top from the second top
        delete p;
    }
}

template <class T>
void Stack<T>::Print(){

    item* p = stackPtr;

    // Print the items from the top to the bottom
    while (p != NULL)
    {
        ReadItem(p);
        p = p->prev;
    }
}


int main(){

    Stack<string> Paul;

    Paul.Push("Paul");
    Paul.Push("Coffee");
    Paul.Push("Lunch");
    Paul.Push("Videos");
    Paul.Print();
    cout << "Popping\n";
    Paul.Pop();
    cout << "Popping\n";
    Paul.Pop();
    cout << "Popping\n";
    Paul.Pop();
    cout << "Popping\n";
    Paul.Pop();
    cout << "Popping\n";
    Paul.Pop();


}
