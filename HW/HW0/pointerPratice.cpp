#include <iostream>
using namespace std;

int main() {
    char a;  
    char *pta; // Declear pointer variable

    a = 'c';
    pta = &a; // The pointer variable pta stores the address of a

    // (void*)¥i¥H¨¾¤î¶Ã½X
    cout << (void*) &a << endl; // Output the address of a                       : 0xbccb7ffbda
    cout << (void*) pta << endl;// Output the pointer variable pta               : 0xbccb7ffbda
    cout << *pta << endl; // Output the value pointer variable pta pointing to   : c
    cout << *&a << endl;  // Use * read the value stored in address &a           : c

}