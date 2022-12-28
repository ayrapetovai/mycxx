#include<iostream>

using namespace std;

int foo() {
    cout << " `foo()`";
    return 2;
}

int bar() {
    cout << " `bar()`";
    return 3;
}

int main() {
    {
        cout << "Order of calls foo and bar `x = foo() + bar()`: ";
        int x = foo() + bar(); // order is no defined
        cout << ". Result is " << x << endl;
    }
}