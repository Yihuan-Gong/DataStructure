#include <iostream>
#include <string.h>
using namespace std;

int main() {

    string input = "Iaa is very sad";
    int pos = input.find(' ');


    cout << input.substr(0, pos);
}