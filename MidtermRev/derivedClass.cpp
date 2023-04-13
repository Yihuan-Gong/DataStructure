#include <iostream>
using namespace std;

int foo = 0;

class Base{
    public:
        Base() {cout << foo << "Base" ;}
};

class A: public Base {
    private:
        int foo;
    public:
        A() { foo=1; cout << foo;}
    friend class B;
};

class B: public Base {
    public:
        void show(A& a) { cout << a.foo << foo;}
};

int main() {
    A a; 
    // B b;
    // b.show(a);
}