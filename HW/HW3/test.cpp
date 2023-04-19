#include <iostream>
using namespace std;


int getNum(string input) {
    string num;

    for (int i = 0; i < input.length(); i++)
        if (isdigit(input[i])) num.push_back(input[i]); 

    return stoi(num);
}

int main() {

    const char *chars = "abc";
    string str = "123*";
    int a;
    
    // for (int i = 0; i < str.length(); i++)
    // {
    //     if (isdigit(str[i])) num.push_back(str[i]); 
    // }

    a = getNum(str);
    a +=10;

    cout << a;
    

    return 0;
}