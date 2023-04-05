#include <iostream>
using namespace std;


struct plate {
    int plateNum;
    int macarons;
    plate* next;
};

class Chain {
private:
    // Should be used only in basic functions
    plate *ptr, *prev, *next;  

public:

    // Basic functions
    void Print();
    bool isEmpty();
    void InsertTail(plate* x);
    void Delete(plate* x, bool deleteMemory);
    void Reverse();
    int CalculateDist(plate* origin, plate* object, int plateLength);
    plate* Find(int plateNum);
    

    // The variables needed in the problem
    plate *current; // In the game, the plate we are using right now
    plate *target;  // The target plate
    plate *head, *tail;
    bool firstRound=true;  

    // Follow the steps 1~5 in the problem discription
    void SelectCurrent();
    Chain& Remove3(Chain& removedPlates);
    void SelectTarget();
    void EatMacarons();
    void InsertAfterTarget(Chain& removedPlates);
    void PrintAns();

    Chain();
};

Chain::Chain() {
    head = tail = NULL;
}


/*******************/
/* BASIC FUNCTIONS */
/*******************/

void Chain::Print() {

    if (isEmpty())
        cout << "The chain is empty" << endl;
    else {
        ptr = tail;
        do {
            ptr = ptr->next;
            cout << "Plate number = " << ptr->plateNum << endl;
            cout << "Macarons = " << ptr->macarons << endl;
            cout << "--------------------"  << endl;
        } while (ptr != tail);
    }
}

bool Chain::isEmpty() {
    return head==NULL && tail==NULL;
}


void Chain::InsertTail(plate* x) {

    if (!isEmpty()) { // Non-empty chain
        tail->next = x;
        tail = tail->next;
        x->next = head;
    } else { // Enpty chain
        head = tail = x;
        x->next = head;
    } 
}

void Chain::Delete(plate* x, bool deleteMemory) {
    /*
        deleteMemory = false : Reconect the chains such that the
                               input node x will be outside the 
                               chain. But the fields stored in x
                               still exsits.
        deleteMemory = true  : Delete the input node x perminantly
    */

    if (head == tail) { // Only one node in the chain
        ptr = head;
        head = tail = NULL;  // Set the chain to be empty
    } 
    else { // Find the node to be deleted
        prev = tail;
        ptr = tail->next;
        while (ptr != x) {
            prev = ptr;
            ptr = ptr->next;
        }

        // Disconect that node
        prev->next = ptr->next;
        if (ptr == tail) 
            tail = prev;
        
        // In case the head node is deleted, we need to 
        // reassign a head node
        head = tail->next;
    }
    
    if (deleteMemory)
        delete ptr;
}

void Chain::Reverse() {

    ptr = head;
    prev = tail;
    next = NULL;

    while (ptr != tail)
    {
        next = ptr->next;
        ptr->next = prev;
        prev = ptr;
        ptr = next;
    }
    ptr->next = prev;

    // Swap the tail and head
    tail = head;
    head = ptr;
}

plate* Chain::Find(int plateNum) {

    ptr = head;
    
    do { 
        if (ptr->plateNum == plateNum)
            return ptr;
        ptr = ptr->next;    
    } while (ptr != head);

    return NULL;
}

int Chain::CalculateDist(plate* origin, plate* object, int plateLength) 
{
    // Calculate the distance from the origin plate
    // dist: the number of nodes to go to object
    // dist > 0 : go CW  to current
    // dist < 0 : go CCW to current

    plate* tracker=origin;
    int dist=0;

    while (tracker != object){
        tracker = tracker->next;
        dist++;
    }

    if (dist >= plateLength/2 + 1)
        dist -= plateLength;

    return dist;
}


/**************************************************/
/* FUNCTIONS ACCORDING TO THE PROBLEM DISCRIPTION */
/**************************************************/

void Chain::SelectCurrent() {

    int currentNum;

    if (firstRound) {
        current = head;
        firstRound = false;
    } 
    else {
        currentNum = (target->plateNum) % 10 + 1;
        current = Find(currentNum);
    }
}


Chain& Chain::Remove3(Chain& removedPlates) {

    plate* temp = current->next;
    plate* front = current->next->next;

    for (int i = 0; i < 3; i++)
    {

        /* Set deleteMemory = false so that the removed plate will 
           still in the memory but not in the chain*/
        Delete(temp, false);

        // Append the removed plate to the tail of new chain: removedPlates
        removedPlates.InsertTail(temp);

        // Move one node forward
        temp = front;
        front = front->next;

        // Debug
        // cout << endl;
        // cout << "i = " << i << endl;
        // cout << endl;
        // Print();
        // cout << endl;
    }

    return removedPlates;
}



struct plateDetail
{
    int plateNum;
    int macarons;
    int dist;
    plate* pointer;
};


void exchange(plateDetail *x1, plateDetail *x2) {
    plateDetail temp = *x1;
    *x1 = *x2;
    *x2 = temp;
}

void find_min(plateDetail *array, int move, int len, int *min_value, int *i_min) 
{
    int i;
    *i_min = move;
    *min_value = (*array).macarons;
    for (i=1;i<len;i++) {
        if (*min_value > (array+i)->macarons) {
            *min_value = (array+i)->macarons;
            *i_min = i+move;
        }
    }
}

void sortMacarons(plateDetail *plates, int plateLength) {

    int i, i_min, min;

    for (i=0; i<plateLength-1; i++) {
        find_min(plates+i, i, plateLength-i, &min, &i_min);
        exchange(plates+i, plates+i_min);
    }
}




void Chain::SelectTarget() {

    
    int plateLength=7;
    int currentIndex;
    int bestMacarons, bestDist, startIndex;
    plateDetail plates[plateLength];

    // cout << "[Unsort]   plateNum/macarons/dist = ";

    /* Put the data into array from the main chain */
    ptr = current;
    for (int i = 0; i < plateLength; i++)
    {
        plates[i].pointer = ptr;
        plates[i].plateNum = ptr->plateNum;
        plates[i].macarons = ptr->macarons;
        if (ptr == current) 
            plates[i].dist = 0;
        else
            plates[i].dist = 100;
            
            
        ptr = ptr->next;

        // cout  << plates[i].plateNum << "/" << plates[i].macarons <<"/" << plates[i].dist << "  ";
    }
    // cout << endl;

    

    // Sort the array according to macarons
    sortMacarons(plates, plateLength);

    // cout << "[Sorted]   plateNum/macarons/dist = ";
    // for (int i = 0; i < plateLength; i++)
    // {
    //     cout  << plates[i].plateNum << "/" << plates[i].macarons <<"/" << plates[i].dist << "  ";
    // }
    // cout << endl;



    // Get the current index from sorted array
    for (int i = 0; i < plateLength; i++)
    {
        if (plates[i].dist == 0)
            currentIndex = i;
    }
    // cout << "currentIndex = " << currentIndex << endl;
    
    // startIndex is used to avoid a plate with same macarons as current plate
    startIndex = currentIndex;
    for (int i = currentIndex-1; i >= 0; i--)
    {
        if (plates[i].macarons == current->macarons)
            startIndex = i;
        else
            break;
    }
    // cout << "startIndex = " << startIndex << endl;
     


    if (startIndex >= 2 || startIndex == 0)  {   

        /* 1. If startIndex >= 2 : 
              Find max macaroms from the plates with macaron 
              less than current. 
           
           2. If startIndex == 0:
              Current has min macarons, so find the max macarons*/
        
        if (startIndex == 0)
            startIndex = plateLength; // Start from the last element
        
        // Assume target is plates[startIndex-1]
        target = plates[startIndex-1].pointer;
        plates[startIndex-1].dist = CalculateDist(current, plates[startIndex-1].pointer, plateLength);
        bestMacarons = plates[startIndex-1].macarons;
        bestDist     = plates[startIndex-1].dist;
        
        // Find is there more suitable target
        for (int i = startIndex-2; i >= 0; i--)
        {
            // Only search for plates with the same macarons as startIndex-1
            if (plates[i].macarons == bestMacarons) 
            {
                plates[i].dist = CalculateDist(current, plates[i].pointer, plateLength);
                
                if (abs(plates[i].dist) < abs(bestDist)){
                    target   = plates[i].pointer;
                    bestDist = plates[i].dist;
                }
                    
                else if (abs(plates[i].dist)==abs(bestDist) && plates[i].dist>0) {
                    target   = plates[i].pointer;
                    bestDist = plates[i].dist;
                }  
            }
            else
                break;
        }
    }
    else if (startIndex == 1) {
        target = plates[0].pointer;
    }

    


}


void Chain::EatMacarons() {

    int k = target->plateNum;

    if (target->macarons < k) {
        target->macarons += 50;
        target->macarons -= k;
    }
    else
        target->macarons -= k;
}

void Chain::InsertAfterTarget(Chain& removedPlates) {
    
    // Join the removedPlates after target
    removedPlates.tail->next = target->next;
    target->next = removedPlates.head;
    if (target == tail) 
        tail = removedPlates.tail;

    // Set the removedPlate to be empty linked list
    // Because all of its nodes has been joined into 
    // the chain
    removedPlates.head = removedPlates.tail = NULL;
}


void Chain::PrintAns() {

    ptr = target;
    do {
        cout << ptr->plateNum << " / ";
        cout << ptr->macarons << "\n";
        ptr = ptr->next;
    } while (ptr != target);

}


int main() {

    Chain plates, removedPlates;
    int macarons;
    int plateNum = 1;

    while (cin >> macarons)
    {
        // Creat a plate (node) 
        plate* x = new plate;
        x->plateNum = plateNum;
        x->macarons = macarons;

        // Append to the tail of the chain
        plates.InsertTail(x);
        plateNum ++;
    }


    for (int i = 0; i < 100; i++)
    {
        // cout << "[i = " << i << " ]" << endl;

        plates.SelectCurrent();
        // cout << "current plate num = " << plates.current->plateNum << endl;

        removedPlates = plates.Remove3(removedPlates);

        //
        // plates.Print();

        plates.SelectTarget();
        // cout << "step 3 finished" << endl;
        // cout << "[SelectTarget] target = " << plates.target->plateNum << endl;

        plates.EatMacarons();

        removedPlates.Reverse();
        plates.InsertAfterTarget(removedPlates);
        
        
        // cout << endl;
        // plates.Print();
        // cout << endl;
        // cout << endl;
        // cout << endl;
    }
    
    plates.PrintAns();
    
    return 0;
}