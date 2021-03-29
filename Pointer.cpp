#include<iostream>
#include<bitset>
#include"Utils.hpp"

using namespace std;

// For a type T, T∗ is the type ‘‘pointer to T.’’
// void* was designed for functions, that are not allowed to do assumptions about type of argument or returning value

int main() {
    cout << "size of pointer (void*) is " << sizeof(void*) << " bytes" << endl;
    {
        char c = 'a';
        char* p = &c; // &c is address, p is adress, same types
        
        //     |-------------|                    |-------------|
        //  p: |      &c     |----address----> c: |     'a'     |
        //     |-------------|                    |-------------|

        cout << "type of &c " << EQUALS_STRING(typeid(&c), typeid(p)) << " type of p" << endl; // ==
        cout << "&c " << EQUALS_STRING(&c, p) << " p" << endl; // == 
        cout << "address of c is " << (int64_t)&c << ", address in p " << (int64_t)p << endl;

        // TODO find out why abouv code: terminating with uncaught exception of type std::invalid_argument: bitset string ctor has invalid argument
        // cout << "address of c is " << bitset<sizeof(void*)*8>(&c) << ", address in p " << bitset<sizeof(void*)*8>(p) << endl;
        // cout << "address of c is " << &c << ", address in p " << p << endl; // TODO why prints values of c in both cases

        char c2 = *p;
        cout << "type of c2 " << EQUALS_STRING(typeid(c2), typeid(*p)) << " type of *p" << endl; // ==
    }
    {
        int** p = nullptr; // pointer to pointer to int
        int* a[15] = {};   // array on 15 pointers to int
    }
    {
        int *pi = new int(0);
        void *pv = pi; // implicit conversion int* to void*
        COMPILATION_ERROR(
            *pv;  // cannot dereference void*, there is no size of 'void' to know how many bytes must be converted
            ++pv; // cannot increment address, size of 'void' is not knowen to be added to address in pv
            int* anotherpi = pv; // cannot initialize typed pointer, when it will be used, there will not be any guaranty that address points to int
        );
        int* anotherpi = static_cast<int*>(pv); // explicit conversion shows intention of treating void* ad address of int, manual guaranty
        double* dp = static_cast<double*>(pv); // unsafe, double can be more wide than int (and it is)
        delete pi;
    }
    {
        // nullptr reprezents empty pointer, it can be assigned to a pointer of any type
        int* pi = nullptr;
        // but not to integral type
        COMPILATION_ERROR(
            int i = nullptr; // Cannot initialize a variable of type 'int' with an rvalue of type 'nullptr_t'
        );
        cout << "NULL " << EQUALS_STRING(NULL, nullptr) << " nullptr" << endl; // ==
        cout << "0 " << EQUALS_STRING(0, nullptr) << " nullptr" << endl; // ==
    }
    {
        // in C the NULL is defined like (void*)0, but in C++ that is illegal
        COMPILATION_ERROR(
            int* pi = (void*)0; // Cannot initialize a variable of type 'int *' with an rvalue of type 'void *'
        );
        cout << "type of NULL is " << typeid(NULL).name() << endl; // long
    }
    {
        // pointer can be "treated as array", by using assecc operator []
        int a[10];
        a[1] = 42;
        cout << "int a[10], type of a is " << typeid(a).name() << endl; // array of 10 integers
        cout << "a[1] is " << a[1] << endl; // 42!
        int* pi = a; // ok
        cout << "type pi is " << typeid(pi).name() << ", and pi[1] is " << pi[1] << endl;
    }
    {
        // type *pointer/&reference + x == address + sizeof(type) * x
        int a[3] = { 1, 2, 3 };
        int* pi = a;
        cout << "type* pinter + 1 (" << (pi + 1) << ") == address + sizeof(type) (" << (&a[1]) << ") " <<  endl;
        cout << "&a[1] + 1 (" << (&a[1] + 1) << ") == &a[2] (" << &a[2] << ") " << endl;
    }
    {
        int a[1];
        int* pi = a;
        COMPILATION_ERROR(
            a = pi; // error: cannot assign pinter to array (based on declaration)
            // The implicit conversion of the array argument to a pointer means that the size of the array is lost
        );
    }
}
