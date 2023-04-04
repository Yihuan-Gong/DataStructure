#include <iostream>
using namespace std;

// void swap(char &a, char &b){
//     char temp;
//     temp = a;
//     a = b;
//     b = temp;
// }

void swap(char *a, char *b) {
    char temp;

    temp = *a;
    *a = *b;
    *b = temp;
}


int main(void) {

    // Declearations
    int str_len, i;
    string input;

    while (cin >> input) // Wait for input in terminal
    {
        // Calculate the lenghth of input string
        str_len = input.length();

        // Reversing string
        for (i=0; i<str_len/2; i++) {
            swap(input[i], input[str_len-i-1]);
        }

        // Output
        cout << input << endl;
    }
    return 0;
}