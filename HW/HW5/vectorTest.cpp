#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

int main() {

    vector<int> vec;
    int a;

    vec.resize(1);
    for (int i = 0; i < 5; i++)
    {
        a = i;
        vec.push_back(a);
    }

    cout << vec.size() << endl;
    


}