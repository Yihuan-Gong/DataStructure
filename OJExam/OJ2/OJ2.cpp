#include <iostream>
#include <string.h>
using namespace std;


struct bead
{
    string color;
    bead* next;
};

class Chain
{
private:
    bead *front, *end, *ptr;
    int len;
    
public:
    bead *stringEnd;

    Chain();
    void Insert(int index, bead *x);
    void InsertEnd(bead *x);
    void Delete(int index, bead *x);
    void Print();
    bool isEmpty() { return front==NULL && end==NULL; }

    int STRING(int shootId);
};

Chain::Chain()
{
    len = 0;
    front = end = NULL;
}

void Chain::Insert(int index, bead *x) {
    ptr = front;

    for (int i = 1; i < index; i++) {
        ptr = ptr->next;
    }

    x->next = ptr->next;
    ptr->next = x; 
}

void Chain::InsertEnd(bead *x) {
    if (isEmpty()) {
        front = end = x;
        x->next = NULL;
    } 
    else {
        end->next = x;
        end = end->next;
        x->next = NULL;
    }
}


void Chain::Print() {
    ptr = front;
    while (ptr != NULL)
    {
        cout << ptr->color << " ";
        ptr = ptr->next;
    }
}


int Chain::STRING(int shootID) {

    int strLen=1, index=1;
    string prevColor;
    bool atROI=false;
    
    ptr = front;
    prevColor = ptr->color;

    while (ptr->next != NULL)
    {
        ptr = ptr->next;
        if (ptr->color == prevColor) {
            strLen += 1;
            prevColor = ptr->color;
            stringEnd = ptr;
            if (index==shootID)
                atROI=true;
        }
        else if (atROI) {
            if (strLen >=3)
                return strLen;
        }
        else {
            strLen = 1;
            prevColor = ptr->color;
        }
        index++;

        
    }
}


int main() {


    string input, shootColor;
    Chain Beads;
    int beadsLen, shootId, strLen;
    int i=0;

    while (cin >> input)
    {
        if (i<3) {
            if (i==0)
                beadsLen = stoi(input);
            else if (i==1)
                shootId = stoi(input);
            else if (i==2)
                shootColor = input;
        } 
        else {
            bead *x = new bead;
            x->color = input;
            Beads.InsertEnd(x);
        }

        i++;
    }


    // Shoot the bead
    bead *x = new bead;
    x->color = shootColor;
    Beads.Insert(shootId, x);

    // 
    strLen = Beads.STRING(shootId);





    cout << endl;
    Beads.Print();
    cout << endl;
    cout << "Finally, strLen = " << strLen;


    
    
    

    // cout << beadsLen + shootId << endl;
    // cout << shootColor << endl;
    


    return 0;
}