#include<iostream>
#include"Utils.hpp"

using namespace std;

void foo_takeing_an_array_of_unknowen_size(int a[]) {
    // Sizeof on array function parameter will return size of 'int *' instead of 'int []' 
    cout << "in function foo: size of a is missing, sizeof is " << sizeof(a) << endl; // cant figure out size of array by pointer, prints 8
    
    // Cannot build range expression with array function parameter 'a' since parameter with array type 'int []' is treated as pointer type 'int *' 
    COMPILATION_ERROR(
        for (int x: a) {}
    );
}

void bar_takeing_an_array_of_size_5(int [5]) {
}

// Array has incomplete element type 'int []'
COMPILATION_ERROR(
    void baz_taking_2darray_of_unknowen_size(int a[][]) {}
    // does not work, becouse a[i][j] is '∗(∗(a+i)+j)', where 'a' is a pointer, to compure 'a+i' compiler must know the size of
    // the object that is pinted by 'a' i. e. first demension
);

// Fortunately, the argument declaration m[][] is illegal because 
// the second dimension of a multidimensional array must be known in order to find the location of an element.
void baz_taking_2darray_fisrt_component_is_of_unknoweni_size(int a[][5], int rows) {
}

int main() {
    {
        int a[1];
        // access operation [i] with array is interpreted as 'array_begin_address + i' 'a + i', as tought 'a' is a pointer
        cout << "array's int element's default value is " << a[0] << endl; // 0, TODO why initialized?
    }
    {
        // size of array is a part of it's type, if it is not a function argument and size is not declared
        int a[] = {1, 2, 3}; // array initializer to the left from =, number of elements is "deduced"
        cout << "type of array contains size: " << typeid(a).name() << endl; // int [3]
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
    {
        int a[] = {1, 2, 3};
        int j = 1;
        cout << "subsripting a build-in array jth element is " << j[a] << endl; // 2
    }
    {
        int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        foo_takeing_an_array_of_unknowen_size(a); // function param is declared as int[] - size of the a is lost
        // compiler does not check sizes of arrays when passing one as function argument
        bar_takeing_an_array_of_size_5(a); // function param is declared as int[5] - size is smaller, then size of the passed argument
    }
    {
        // 2D arrays are alligned in memory continuously
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
        int a[3][5]; // a is an array of arrays
        cout << "size of a" << sizeof(a) << endl; // 3
        cout << "address of beginig of a is " << &a << ", address of the second element (arrays) of a is " << (a + 1) << endl; 
        cout << "ditance in bytes betwin 1st and 2nd elements (arrays) of 'int a[3][5]' is ";
        cout  << (reinterpret_cast<char*>(a + 1) - reinterpret_cast<char*>(&a)) << endl; // 20, becouse each a's element is int[5]
    }
    {
        int a[3][5];
        // function is declared as void (*name)(int [][5], int rows)
        baz_taking_2darray_fisrt_component_is_of_unknoweni_size(a, 3);
    }
}
