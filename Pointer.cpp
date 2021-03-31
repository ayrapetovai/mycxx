#include<iostream>
#include<bitset>
#include"Utils.hpp"

using namespace std;

// For a type T, T∗ is the type ‘‘pointer to T.’’
// void* was designed for functions, that are not allowed to do assumptions about type of argument or returning value

// C++ offers two related meanings of ‘‘constant’’:
// • constexpr: Evaluate at compile time
// • const: Do not modify in this scope

// use const T& reference to prevent modification
// use T&& reference implement "destructive read", instead of "deep copy"


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

        // TODO find out why does above code terminate with uncaught exception of type std::invalid_argument: bitset string ctor has invalid argument
        RUNTIME_ERROR(
            cout << "address of c is " << bitset<sizeof(void*)*8>(&c) << ", address in p " << bitset<sizeof(void*)*8>(p) << endl;
            cout << "address of c is " << &c << ", address in p " << p << endl; // TODO why prints values of c in both cases
        );

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
            // The implicit conversion of the array variable to a pointer means that the size of the array is lost
        );
    }
    {
        double* a[10];
        int dist = reinterpret_cast<char*>(a+2) - reinterpret_cast<char*>(a); 
        cout << "distance in bytes is " << dist << endl; // 16
    }
// const
    {
        // const influicing on a name to it's right.
        // When using a pointer, two objects are involved: the pointer itself and the object pointed to.
        // ‘‘Pre- fixing’’ a declaration of a pointer with const makes the object, but not the pointer, a constant.
        // To declare a pointer itself, rather than the object pointed to, to be a constant, we use the declarator operator ∗const instead of plain ∗.
        const char *chp = new char[]{ "abc" }; // pinter can be modified, but char string - cannot be modified;
        COMPILATION_ERROR(
            chp[0] = 'A';
        );
        delete [] chp;
        chp = new char[]{ "def" }; // ok
        delete [] chp;

        char * const cp = new char[]{ "abc" }; // pointer cannot be modifier, but value can be modified.
        // ! the operator that makes cp constant is '* const' !
        cp[0] = 'A';
        COMPILATION_ERROR(
            cp = new int[]{ "def" };
        );
        delete [] cp;

        // however... there are no operator 'const *', only '* const'
        char const *p = "abc"; // is a variable pointer to const char, as conat char *p
        cout << "char const* " << EQUALS_STRING(typeid(char const*), typeid(const char*)) << " const char*" << endl;
    }
// T& - lvalue reference, non-const can bind to lvalue, const can bing to rvalue
    {
        const int x = 42;
        const int* p = &x; // ok, p guaranties that value of x will not be changes throw it
        // What is the rull? C++ is "const safety"?
        COMPILATION_ERROR(
            int* const p = &x; // now p guaranties to point only to x, and does not guarantee that x will not be changed
        );
    }
    {
        const int& r = 2; // kind of abstraction...
        int a = 13, b = 42;
        COMPILATION_ERROR(
            int& r = 3;       // 3 is an rvalue, if reference is not const, it cannot guarantee writ to 1 (1 is not an object, it is value in assembly command)
            int& tmp = a + b; // same thing
        );

        const int& tmp = a + b; // intermidiate value of a + b is placed in a temporary variable (an object, it has an address)
        /* there are 3 objects on the stack
         mov     dword ptr [rbp - 8], 13      # stack['a'] := 13                     # first object
         mov     dword ptr [rbp - 12], 42     # stack['b'] := 42                     # second object
         mov     eax, dword ptr [rbp - 8]     # reg[eax] := stack['a']
         add     eax, dword ptr [rbp - 12]    # reg[eax] := reg[eax] + stack['b']
         mov     dword ptr [rbp - 28], eax    # stack['tmp'] := reg[eax]             # third object
         */
        cout << "tmp is an ojbect? value " << tmp << ", type " << typeid(tmp).name() << ", size " << sizeof(tmp) << ", address " << &tmp << endl;
    }
// T&& - rvalue reference, non-const can bind to a rvalue, const can bing to a rvalue, const cannot bing to lvalue, because 'const' means "do not modifiy", but && says "read destructivly" (take ovnership)
    {
        int&& r = 3; // ok, binds to a temporaty value, compare to 'int& r = 3', wich does not compile
        int x = 3;
        COMPILATION_ERROR(
            const int&& r = x; // Rvalue reference to type 'const int' cannot bind to lvalue of type 'int'
            int&& r = x;      // Rvalue reference to type 'int' cannot bind to lvalue of type 'int'
        );
    }
    {
        // TODO does not work!
        char s[] = "Hello!";
        char* p = s;
        cout << "message: ";
        while(*p) {
            cout << ++*p; // this ++*p does not increasing letter codes... as *p++
        }
        cout << endl;
    }
    {
        // null reference
        COMPILATION_ERROR(
            int& x = *(nullptr); // Indirection requires pointer operand ('nullptr_t' invalid)
        );
        int& x = *((int*)nullptr); // no runtime error, but the code is invalid
        RUNTIME_ERROR(
            int a = x * 2; // Segmentation fault, x is 0
        );
    }
}
