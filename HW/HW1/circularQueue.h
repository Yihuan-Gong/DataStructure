#include <iostream>
using namespace std;

template <class T>
class Queue
{
private:
    int front, rear, size;
    T* nums;
    void resize();

public:
    void enqueue(T data);
    void dequeue();
    void peek();
    bool isEmpty();
    bool isFull();

    Queue(int initialSize);
    ~Queue();
};