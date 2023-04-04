#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;


string* splitStr(string inputStr) {
    
    int lenStr = inputStr.length();
    bool secondStr=false;
    string* output = new string[2];

    for (int i = 0; i < lenStr; i++)
    {
        if (secondStr) {
            output[1] += inputStr[i];
        }
        else if (inputStr[i] == ' ')
            secondStr = true;
        else 
            output[0] += inputStr[i];
    }
    
    return output;
}

// int* spiltInt()


int main() {

    string input, leavingOrder, toastingOrder;
    string* nameTime, tableCups;
    bool leaving=false, toasting=false;
    int totalCups=0;

    stack<string> names;
    stack<string> times;
    queue<string> tables;

    while (getline(cin, input))
    {
        if (input == "R"){
            leaving = true;
            continue;
        }
            
        else if (input == "T") {
            toasting = true;
            continue;
        }
           

        if (leaving) {
            nameTime = splitStr(input);
            names.push(nameTime[0]);
            times.push(nameTime[1]);
            leaving = false;
        }
        else if (toasting) {
            tableCups = splitStr(input);
            tables.push(tableCups[0]);
            // totalCups += stoi(tableCups[1]);
        }
    }



    while (true)
    {
        leavingOrder += names.top();
        names.pop();
        if (names.empty() == false)
            leavingOrder += " ";
        else
            break;
    }

    while (true)
    {
        toastingOrder += tables.front();
        tables.pop();
        if (tables.empty() == false)
            toastingOrder += " ";
        else
            break;
    }
    


    cout << leavingOrder << "\n";
    cout << toastingOrder << "\n";
    
}