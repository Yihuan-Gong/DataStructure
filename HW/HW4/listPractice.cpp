#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<list>
#include<string.h>
#include<cmath>
using namespace std;




void printList(list<int> input) {
    for (list<int>::iterator i = input.begin(); i != input.end(); ++i) 
        cout << *i << "  ";
    cout << endl;
}


int main() {

    list<int> a = {1, 2, 3, 4};
    printList(a);

    a.push_back(5);
    printList(a);

    return 0;
}