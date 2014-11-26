#include <iostream>

using namespace std;

class A {
    int data;
public:
    A(int i) : data(i) { }

    int read() const {
        return data;
    }
    void set(int val) {
        data = val;
    }
};

class Aref {
    A &ref;
public:
/*
    Aref(A &a) : ref(a) 
    {
        cout << "Call Aref(A &a)\n";
    }
*/
// added this constructor to allow [1]:
    Aref(const A &a) 
    : ref(const_cast<A&>(a))
    {
        cout << "Call Aref(const A &a)\n";
    }
// but it is not possible to declare a constructor const
// to disallow [2]!

    int read() const {
        return ref.read();
    }
    void set(int val) {
        ref.set(val);
    }
};

int main() {
    const A a = 1;
    const Aref ar1 = a; // should be allowed [1]
    Aref ar2 = a; // should be illegal [2]
    ar2.set(3);
    A ax = 1;
    const Aref arx = ax; // should be allowed [1]
}
