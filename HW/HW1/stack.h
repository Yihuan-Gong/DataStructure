#include <iostream>
using namespace std;

template <class T>
class Stack {
private:
    struct item{
        T value;
        item* prev;
    };
    item* stackPtr;

public:
    void Push(T value);
    void Pop();
    void ReadItem(item* r);
    void Print();

    Stack();
    ~Stack();
};