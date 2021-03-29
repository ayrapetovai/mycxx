#include<iostream>
#include"Utils.hpp"

using namespace std;

int main() {
    {
        int a[1];
        cout << "array's int element's default value is " << a[0] << endl; // 0, TODO why initialized?
    }
    {
        int a[] = {1, 2, 3}; // array initializer to the left from =, number of elements is "deduced"
        cout << "sizeof a is " << sizeof(a) << " bytes" << endl; // 12
        cout << "number of elements in a is " << sizeof(a)/sizeof(int) << endl;

        cout << "print a's elements:";
        for (const int x: a) {
            cout << " " << x;
        }
        cout << endl;
    }
    {
        int a[1];
        int b[1];
        COMPILATION_ERROR(
            a = b; // error : no array assignment exists in C++
        );
    }
    {
        int a[1];
        COMPILATION_ERROR(
            int b[1] = a; // error : cant copy array, no implicit array copy in C++
        );
    }
    // TODO std::array
    // TODO std::valarray
}
