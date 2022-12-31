#include <iostream>
#include <array>
#include "Utils.hpp"

using namespace std;

// Array is a continuous object in memory, nowhere in memory is writen its length.
// int a[] = { 1, 2, 3 };
// int *ap = a;
// Array access `a[i]` is same as `*(ap + i)`, types of `a` and `ap` are different. Array access dereferencing.
// *(ap + i) == *(((void*) ap) + sizeof(int) * i);
// Only for pointers and integer indexes:
// a[j] == *(&a[0]+j) == *(a+j) == *(j+a) == j[a]
// 3["Texas"] == "Texas"[3] == 'a'

void foo_taking_an_array_of_unknown_size(int a[]) {
    // Sizeof on array function parameter will return size of 'int *' instead of 'int []' 
    cout << "in function foo: size of `a` is missing, sizeof is " << sizeof(a) << endl; // cant figure out size of array by pointer, prints 8 - size of `int*`

    // Cannot build range expression with array function parameter 'a' since parameter with array type 'int []' is treated as pointer type 'int *' 
    COMPILATION_ERROR(
        for (int x: a) {}
    );
}

void bar_taking_an_array_of_size_5(int [5]) {
}

// Array has incomplete element type 'int []'
COMPILATION_ERROR(
    void baz_taking_2d_array_of_unknown_size(int a[][]) {}
    // does not work, because a[i][j] is '∗(∗(a+i)+j)', where 'a' is a pointer, to compute 'a+i' compiler must know the size of
    // the object that is printed by 'a' i. e. first dimension
);

// Fortunately, the argument declaration m[][] is illegal because 
// the second dimension of a multidimensional array must be known in order to find the location of an element.
void baz_taking_2d_array_first_component_is_of_unknown_size(int a[][5], int rows) {
}

int main() {
    {
        int a[1];
        // access operation [i] with array is interpreted as 'array_begin_address + i' 'a + i', as thought 'a' is a pointer
        cout << "array's int element's default value is " << a[0] << endl; // 0, TODO why initialized?
    }
    {
        // size of array is a part of its type, if it is not a function argument and size is not declared
        int a[] = {1, 2, 3}; // array initializer to the left from =, number of elements is "deduced"
        cout << "type of array `a` with size is `" << describe_type(typeid(a).name()) << "`" << endl; // int [3]
        cout << "sizeof `a` is " << sizeof(a) << " bytes" << endl; // 12
        cout << "number of elements in `a` is " << sizeof(a)/sizeof(int) << endl;

        cout << "print `a`'s elements:";
        for (const int x: a) {
            cout << " " << x;
        }
        cout << endl;
    }
    {
        int a[] = { [10] = 1, [2] = 3 }; // { 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1 }
        int b[] = { [0 ... 10] = 1, [12 ... 15] = 7 }; // { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 7, 7 }

        cout << "{ [10] = 1, [2] = 3 } is ";
        std::copy(a, a + sizeof(a)/sizeof(a[0]), std::ostream_iterator<int>(std::cout, " "));
        cout << endl;
        cout << "{[0 ... 10] = 1, [12 ... 15] = 7} is ";
        std::copy(b, b + sizeof(b)/sizeof(b[0]), std::ostream_iterator<int>(std::cout, " "));
        cout << endl;
    }
    {
        int a[1];
        int b[1];
        COMPILATION_ERROR(
            a = b; // error : no array assignment exists in C++
        );
        int *ap = a;
        int *bp = b;
        ap = bp; // ok, pointer assignment, compiler watch declaration of variables: `a` is an array, whereas `ap` is a pointer to int.
    }
    {
        int a[1];
        COMPILATION_ERROR(
            int b[1] = a; // error : cant copy array, no implicit array copy in C++
        );
    }
    {
        int a[] = {};
        int* int_p = nullptr;

        COMPILATION_ERROR(
            // Array type 'int[0]' is not assignable
            a = int_p;
        )
    }
    {
        // range-for works for arrays of known size
        int a[10] = {};
        for (int x: a) {
            // OK
        }

        int s = 1;
        int aa[s + 1];
        aa[0] = 777;
        aa[1] = 888;
        cout << "begin iterating over `int aa[s]`: ";
        // TODO how the hack this can work?
        for (int x: aa) { // OK
            cout << x << " "; // outputs "777 888 "
        }
        cout << "; end iterating." << endl;

        // despite the declaration of a function parameter as arrays it is always a pointer:
        cout << "void bar_taking_an_array_of_size_5(int a[5]) type is " << describe_type(typeid(bar_taking_an_array_of_size_5).name()) << endl;
        // prints: void (int*)

        // in this lambda `a` is an array of unknown size
        auto foo = [](int a[]){
            // Cannot build range expression with array function parameter 'a' since parameter with array type 'int[]' is treated as pointer type 'int *'
            COMPILATION_ERROR(
                for (int x: a) {}
            )
            int* int_p = nullptr;
            a = int_p; // OK, `int a[]` is a function's parameter, treated as a pointer
        };
        foo(aa);

        // yet, in this lambda `a` cannot be used in rage-for, because arrays a passed to functions only as pointers.
        auto bar = [](int a[3]) {
            // Cannot build range expression with array function parameter 'a' since parameter with array type 'int[3]' is treated as pointer type 'int *'
            COMPILATION_ERROR(
                for (int x: a) {}
            )
            int* int_p = nullptr;
            a = int_p; // OK, `int a[]` is a function's parameter, treated as a pointer
        };
        bar(aa); // `aa` is `int aa[1]`, no size checks

        // range-for does not work for pointers
        int *ap = a;
        COMPILATION_ERROR(
            // Invalid range expression of type 'int *'; no viable 'begin' function available
            for (int x: ap) {}
        )

        auto baz = [](array<int, 3> ar) {
            for (int x: ar) {} // OK
            auto [a, y, z] = ar; // OK
        };
        baz(array<int, 3>{ 1, 2 });

        COMPILATION_ERROR(
            // No matching function for call to object of type 'void (*)(array<int, 2>)'
            baz(array<int, 2>{ 1, 2 });
        )
    }
    // TODO std::array
    // TODO std::valarray
    {
        int a[] = {1, 2, 3};
        int j = 1;
        cout << "subscripting a build-in array jth element is " << j[a] << endl; // 2
    }
    {
        int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        foo_taking_an_array_of_unknown_size(a); // function param is declared as int[] - size of the `a` is lost
        // compiler does not check sizes of arrays when passing one as function argument
        bar_taking_an_array_of_size_5(a); // function param is declared as int[5] - size is smaller, then size of the passed argument
    }
    {
        // 2D arrays are aligned in memory continuously
        const int rows = 3;
        const int columns = 5;
        int a[3][5];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                a[i][j] = 10*i + j;
            }
        }
        cout << "array content:";
        // int* p = a // error: no implicit conversion from pointer of different type
        for (int *p = reinterpret_cast<int*>(a); p != reinterpret_cast<int*>(a) + rows * columns; p++) {
            cout << " " << *p;
        }
        cout << endl;
        // out: 0 1 2 3 4 10 11 12 13 14 20 21 22 23 24
    }
    {
        int a[3][5]; // `a` is an array of arrays
        cout << "size of a" << sizeof(a) << endl; // 3
        cout << "address of beginning of a is " << &a << ", address of the second element (arrays) of a is " << (a + 1) << endl;
        cout << "distance in bytes between 1st and 2nd elements (arrays) of 'int a[3][5]' is ";
        cout  << (reinterpret_cast<char*>(a + 1) - reinterpret_cast<char*>(&a)) << endl; // 20, because each a's element is int[5]
    }
    {
        int a[3][5];
        // function is declared as void (*name)(int [][5], int rows)
        baz_taking_2d_array_first_component_is_of_unknown_size(a, 3);
    }
    {
        int size = 10;
        int a[size]; // size is not a constexpr, OK
    }
}
