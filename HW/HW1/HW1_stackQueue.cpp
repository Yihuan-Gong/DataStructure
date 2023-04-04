#include <iostream>
#include <string>
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
    T dequeue();
    void peek();
    bool isEmpty();
    bool isFull();

    Queue(int initialSize);
    ~Queue();
};


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
    T Pop();
    T ReadItem(item* r);
    void Print();
    bool isEmpty();

    Stack();
    ~Stack();
};



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
T Queue<T>::dequeue() {
    if (isEmpty()){
        cout << "The queue is empty !" << endl;
        throw exception();
    }

    T temp = nums[front];  // Read the element going out the queue
    
    // Move the front pointer to the next element
    if (front == rear) // True => Only one element in the queue
        front = rear = -1;
    else
        front = (front+1) % size;
    
    return temp;
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
    T* tempArr = new T[newSize];
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

    if(isEmpty())
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
T Stack<T>::ReadItem(item* r) {
    return r->value;
}

template <class T>
T Stack<T>::Pop() {

    if(stackPtr == NULL){
        cout << "There is nothing on the stack\n";
        throw exception();
    }

    item* p = stackPtr;  // p points to the top
    T temp = ReadItem(p);
    stackPtr = stackPtr->prev; // stackPtr point to the second top,
                                // since the first top will be deleted
    p->prev = NULL;  // Disconect the first top from the second top
    delete p;
    return temp;
}


template <class T>
void Stack<T>::Print(){

    item* p = stackPtr;

    // Print the items from the top to the bottom
    while (p != NULL)
    {
        cout << "value = " << ReadItem(p) << endl;
        p = p->prev;
    }
}

template <class T>
bool Stack<T>::isEmpty() {
    return stackPtr==NULL;
}


int getPoints(int gold){
    switch (gold)
    {
    case 3:
        return 500;
    case 2:
        return 300;
    case 1:
        return 150;
    default:
        return 50;
    }
}

template <class T>
int countPoints(Queue<T> queue, bool miss) {
    
    int ignoreTreasures=0;
    int totalPoints=0;
    int gold=0, silver=0;
    string tag;
    string treasures[3];

    while (queue.isEmpty() == false)
    {
        tag = queue.dequeue();
        
        if (tag == "MISS") {
            if (miss)
                ignoreTreasures = 4;
        }
        else {  // tag == "GOLD" or "SILVER"
            if (ignoreTreasures != 0)
                ignoreTreasures --;
            else {
                // Collect treasures
                if (tag == "GOLD")
                    gold ++;
                else
                    silver ++;

                // When collect 3 treasures, count the points
                if (gold + silver == 3) {
                    totalPoints += getPoints(gold);
                    gold = silver = 0; // Reset treasure for next collection 
                }
            }
        }
    }

    return totalPoints;
}

// template <class T>
// string getReturnPath(Stack<T> stack) {

//     string tagLR, returnRoad;

//     while (true)
//     {
//         tagLR = stack.Pop();
//         // Do: TL <-> TR
//         if (tagLR == "TL")
//             tagLR = "TR";
//         else
//             tagLR = "TL";

//         returnRoad += tagLR;
//         if (stack.isEmpty())
//             break;
//         returnRoad += "->";
//     }

//     return returnRoad;
// }


int main() {

    string input;
    string returnRoad;
    int ptNoMiss, ptMiss;

    Queue<string> queue(3);
    Stack<string> stack;

    // Take the input
    while (cin >> input)
    {
        if (input == "TL" || input == "TR") 
            stack.Push(input);
        else if (input == "GOLD" || input == "SILVER" || input == "MISS")
            queue.enqueue(input);
    }


    // Return road
    string tagLR;
    while (true)
    {
        tagLR = stack.Pop();
        // Do: TL <-> TR
        if (tagLR == "TL")
            tagLR = "TR";
        else
            tagLR = "TL";

        returnRoad += tagLR;
        if (stack.isEmpty())
            break;
        returnRoad += "->";
    }

    
    // Count the points
    ptMiss   = countPoints(queue, true);
    ptNoMiss = countPoints(queue, false);


    // Print the result
    cout << returnRoad << endl;
    cout << ptMiss << endl;
    cout << ptNoMiss << endl;
}