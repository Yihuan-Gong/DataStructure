#include <iostream>
#include "circularQueue.h"

using namespace std;

template <class T>
Queue<T>::Queue(int initialSize)
{
    front = rear = -1;
    size = initialSize;
    nums = new T[initialSize];
}

template <class T>
Queue<T>::~Queue()
{
}

template <class T>
void Queue<T>::enqueue(T data) {
    if(isFull())
        resize();
    else if(isEmpty())
        front++;  /* Front is intialized to -1. So we need to 
                   add set front to 0 when first element enters the queue */
    rear = (rear+1) % size;  /* This is the place to put the data entering the queue
                                Remember to reset the size when resize */
    nums[rear] = data;
}

template <class T>
void Queue<T>::dequeue() {
    if (isEmpty()){
        cout << "The queue is empty !" << endl;
        return;
    }

    int temp = nums[front];  // Read the element going out the queue
    
    // Move the front pointer to the next element
    if (front == rear) // True => Only one element in the queue
        front = rear = -1;
    else
        front = (front+1) % size;
    
    cout << "value = " << temp << endl;
    return;
}

template <class T>
void Queue<T>::peek() {
    if(isEmpty()) {
        cout << "The queue is empty !" << endl;
        return;
    }
    cout << "peek is " << nums[front] << endl;
    return;
}

template <class T>
bool Queue<T>::isEmpty() {
    return front == -1;
}

template <class T>
bool Queue<T>::isFull() {
    return (rear+1)%size == front;
}

template <class T>
void Queue<T>::resize() {

    int newSize = size*2; // double the size of queue 
    int* tempArr = new int[newSize];
    int i = 0;     // The index for new array
    int j = front; // The index for old array

    /* Move elements in old array to new array 
       and the front of old array goes to the 
       index 0 of the new array */
    do {
        tempArr[i++] = nums[j];
        j = (j+1) % size;
    } while(j != front);

    // Now reset all things for the new array
    front = 0;
    rear = size - 1; // Note here size is the length of old array
    size = newSize;
    nums = tempArr;
}



int main() {

    Queue<int> queue(3);

    queue.enqueue(5);
    queue.enqueue(8);
    queue.enqueue(12);
    queue.enqueue(9);
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();

}