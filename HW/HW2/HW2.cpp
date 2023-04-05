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


void Chain::SelectTarget() {

    int currentMacarons = current->macarons;
    int maxMacarons = 0;
    int dist1=0, dist2=0;
    bool sameMacarons = false;
    plate *sameCloset;
    plate *p, *tracker1, *tracker2;
    


    /* STEP1 : The candidate plates have smaller number of macarons than the 
       current plate. From the candidate plates, choose the one with the most 
       macarons. */
        
    ptr = current;
    while (ptr->next != current)
    {
        ptr = ptr->next;
        if (ptr->macarons > maxMacarons && ptr->macarons < currentMacarons) {
            target = ptr;
            maxMacarons = ptr->macarons;
        }
    }

    if (maxMacarons == 0) 
    {  
        // Current plate has fewest macarons, 
        // so find the plate with the most macarons
        ptr = current;
        while (ptr->next != current)
        {
            ptr = ptr->next;
            if (ptr->macarons > maxMacarons) {
                target = ptr;
                maxMacarons = ptr->macarons;
            }
        }
    }



    /* STEP2 : If multiple plates have the same number of macarons and that 
       "number" is the what we determined on the STEP1, choose the plate 
       that is closet to current*/
    ptr = current;
    while (ptr->next != current)
    {
        ptr = ptr->next;
        // cout << "now ptr = " << ptr->plateNum << endl;
        p = ptr;
        // p = ptr->next;

        while (p->next != current) {  // p != current
            p = p->next;
            // cout << "now p = " << p->plateNum << endl;
            if (p->macarons == ptr->macarons) {
                // cout << "True at (ptr, p) = " ;
                // cout << "(" << ptr->plateNum << ", " << p->plateNum << ")" << endl;
                sameMacarons = true;
                break;
            }

        }

        if (sameMacarons) 
            break;  
    }
    if (sameMacarons) 
    {
        // Calculate the distance from the current plate
        // dist1 for ptr;  dist2 for p
        // dist: the number of nodes to go to current
        // dist > 0 : go CW  to current
        // dist < 0 : go CCW to current

        tracker1 = ptr;
        tracker2 = p;

        // cout << "True at (ptr, p) = " ;
        // cout << "(" << ptr->plateNum << ", " << p->plateNum << ")" << endl;

        while (tracker1 != current) {
            tracker1 = tracker1->next;
            dist1 ++;
        }
        if (dist1 >= 4)
            dist1 -= 7;

        while (tracker2 != current) {
            tracker2 = tracker2->next;
            dist2 ++;
        }
        if (dist2 >=4)
            dist2 -=7;

        // cout << "dist1 = " << dist1 << endl;
        // cout << "dist2 = " << dist2 << endl;
        
        if(abs(dist1) > abs(dist2)) {
            sameCloset = p;
            // cout << "1>2" << endl;
            // cout << "target = " << target->plateNum << endl;
        }   
        else if (abs(dist1) < abs(dist2)) {
            sameCloset = ptr;
            // cout << "2>1" << endl;
            // cout << "target = " << target->plateNum << endl;
        }
        else {
            if (dist1<0)
                sameCloset = ptr;
            else
                sameCloset = p;
        }

        // Most important
        if (sameCloset->macarons == target->macarons) 
            target = sameCloset;
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
        // cout << "step 1 finished" << endl;
        // cout << "current = " << plates.current->plateNum << endl;

        removedPlates = plates.Remove3(removedPlates);
        // cout << "step 2 finished" << endl;
        // cout << "removed plate is " << endl;
        // removedPlates.Print();
        // cout << "###################" << endl;
        // cout << "main chain is " << endl;
        // plates.Print();

        plates.SelectTarget();
        // cout << "step 3 finished" << endl;
        // cout << "[SelectTarget] target = " << plates.target->plateNum << endl;

        plates.EatMacarons();
        // cout << "step 4 finished" << endl;
        // cout << "After eating at target, macarons = " << plates.target->macarons << endl;

        removedPlates.Reverse();
        plates.InsertAfterTarget(removedPlates);
        // cout << "step 5 finished" << endl;
        // cout << "After putting back, the chain is : " << endl;
        // cout << endl;
        // plates.Print();

        // cout << endl;
        // cout << endl;
        // cout << endl;
        // // cout << "Now target is " << plates.target->plateNum << endl;
        // // cout << "After eating at target, macarons = " << plates.target->macarons << endl;
        // // cout << endl;

        
        // cout << endl;
        // plates.Print();
        // cout << endl;
        // cout << endl;
        // cout << endl;
    }
    
    plates.PrintAns();

    // plates.Print();
    // cout << endl;
    // cout << "Original order: " << endl;
    // removedPlates.Print();
    // cout << "Reversed order: " << endl;
    // removedPlates.Reverse();
    // removedPlates.Print();

    return 0;
}