#include <iostream>
#include <string>
using namespace std;

int main(void){
  
  int* nums = new int[3];
  
  nums[0] = 2;
  nums[1] = 3;
  nums[2] = 4;

  for (int i = 0; i < 3; i++)
  {
    cout << nums[i] << endl;
  }
  
  
  return 0;
}