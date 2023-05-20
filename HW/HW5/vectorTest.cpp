#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

int main() {

    vector<int> vec;
    int a;

    for (int i = 0; i < 5; i++)
    {
        a = i;
        vec.reserve(10);
        vec[i] = a;
        // vec.push_back(a);

        cout << vec[i] << endl;
    }

    
    


}