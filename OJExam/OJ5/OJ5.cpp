#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct Pastry {
    int id;
    int p; // position
    unsigned long price;
    string type;
};

int main()
{
    string input;
    int n; // Months 
    int m; // Number of types
    int i=0;
    int id, month;
    bool firstMonth = true;
    Pastry pastry;
    vector<Pastry> pastries, pastries_copy;
    vector<int> orderTable, v;


    


    while (cin >> input)
    {
        if (i==0)
            n = stoi(input);
        else if (i==1) {
            m = stoi(input);
            orderTable.resize(m*n);
            v.resize(m);
        }
        else if (i>=2 && i<m+2) {
            pastry.id = i-2;
            // cout << pastry.id << endl;
            pastry.type = input;
            pastries.push_back(pastry);
        }
        else if (i>=m+2) 
        {
            id = (i-(m+2))%m;
            month = (i-(m+2))/m;
            pastries[id].price = stoi(input);

            // Sort the price
            if (id == m-1) 
            {
                pastries_copy = pastries;

                // sort a vector, use stable_sort if order has to be persisted
                std::sort(pastries_copy.begin(), pastries_copy.end(), [](auto& left, auto& right) {
                    return left.price < right.price;
                });
                // vector is now sorted in ascending order

                for (int j = 0; i < m; i++)
                {
                    cout << pastries_copy[j].price << " ";
                }
                

                // cout << "kkk" << endl;

                // Write order to the order table
                for (int order=0; order<m; order++)
                {
                    int k = pastries_copy[order].id;
                    orderTable[month*m + k] = order;
                }
                    

            }
        }
        
        i++;
    }





    // for (int i = 0; i < m*n; i++)
    // {
    //     if (i%m == 0)
    //         cout << endl;
        
    //     cout << orderTable[i] << " ";
    // }
    // cout << endl;
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n-1; j++)
        {
            v[i] += abs(orderTable[j*m + i] - orderTable[(j+1)*m + i]);
        }
        
        // cout << v[i] << endl;
        
    }

    
    int min = 51568448;
    int yesId;
    for (int i = 0; i < m; i++)
    {
        if (v[i] < min)
        {
            yesId = i;
            min = v[i];
        }
    }
    // cout << yesId << endl;
    

    cout << pastries[yesId].type << "\n";
    
}