#include <iostream>
#include <array>

using namespace std;

int foo(int x) {
    cout << " foo(" << x<< ")";
    return x;
}

int wah(int x) {
    cout << " wah(" << x << ")";
    return x;
}

int bar(int x) {
    cout << " bar(" << x << ")";
    return x;
}

int baz(int x) {
    cout << " baz" << x << ")";
    return x;
}

void biconsumer(int x, int y) {
}

int main() {
    {
        // order of evaluation is undefined
        cout << "x=foo(1) + bar(2) ";
        int x = foo(1) + bar(2);
        cout << endl;
    }
    {
        // order of evaluaion is undefined: foo(bar()) or wah(baz())
        cout << "x=foo(bar(1)) + wah(baz(2)) ";
        int x = foo(bar(1)) + wah(baz(2));
        cout << endl;
    }
    {
        // order of evaluation is undefined
        array<int, 2> a = { 13, 42 };
        int i = 0;
        a[i] = i++; // undefined, Unsequenced modification and access to 'i'

        cout << "array is " << a[0] << ", " << a[1] << "; i is " << i << endl;
    }
    {
        // evaluation order of function arguments is undefined
        cout << "biconsumer(foo(1), bar(2) ";
        biconsumer(foo(1), bar(2));
        cout << endl;
    }
}
