#include<iostream>
#include "Utils.hpp"

using namespace std;

// if no initializer specified then:
// global, namespace, local static and static (collectively calld static objects) is initialized to {} - default initializer

int global_variable;

int main() {
    {
        // initializer syntax
        int x1{ 1 };    // TODO call {} initializer list construtor sematics?
        int x2 = { 2 }; // use constructor; wich of () and {}, is intializer_list is created? does it occupy memory?
        int x3 = 3;     // TODO copy/move constructor sematics?
        int x4(4);      // TODO copy/move constructor sematics?
        cout << "x[i] in (" << x1 << ", " << x2 << ", " << x3 << ", " << x4 << ")" << endl;
    }
    {
        // list initialization {} does not allow narrowing - when initial value has to be truncated
        WILL_NOT_COMPILE(
            short x{ 1000000 }; // compilation error: 1000000 requires truncating
        );
        short x{ (short)1000000 }; // ok: (sort) 1000000 is truncated explicitly

        WILL_NOT_COMPILE(
            int x{ 0.0f }; // float|double -/-> int|short|long
        );

        // TODO Stroustrup says no, but acutaly it is compile in vc++17, check on mac os    
        WILL_NOT_COMPILE(
            double xx{ 1 }; // int|short|long -/-> float|double
        );

        // TODO Stroustrup says no, but acutaly it is compile in vc++17, check on mac os
        WILL_NOT_COMPILE(
            float x{ 0.0 }; // here, 0.0 is double, double -/-> float
        );
        {
            // TODO Stroustrup says: z is an initializer_list<int>, but it is int in vc++17, what is no mac os?
            auto z{ 99 };
            cout << "auto z1{ 99 } is " << typeid(z).name() << endl;
            // I like z to be int in this syntax...
        }
        {
            auto z = { 99 };
            cout << "auto z1{ 99 } is " << typeid(z).name() << endl;
        }
        {
            int x{}; // TODO what constructor is called? Where does initial value comes from?
            cout << "int x{} " << EQUALS_STRING(x, int(0)) << " int(0), or 0, or int()" << endl;
        }
        {
            int* pi{};
            cout << "int *pi{} " << EQUALS_STRING(pi, nullptr) << " nullptr, int *pi{} " << EQUALS_STRING(pi, NULL) << " NULL, int *pi{} " << EQUALS_STRING(pi, 0) << " 0" <<  endl;
        }
        // TODO constructors, https://en.cppreference.com/w/cpp/language/value_category, deleted constructors, move
        {
            // TODO does buffer_size variable exist in runtime? Does it occupy memory?
            constexpr int buffer_size = 120; // calculated at compile time
            char buf1[buffer_size]{};    // buf1 is arrays of buffer_size chars intialized with 0
            char buf2[buffer_size] = {}; // buf2 is arrays of buffer_size chars intialized with 0
        }
        {
            // global_variable is defined at the begining
#pragma warning(suppress: 4101) // unused local variable
            int local_variable;
            cout << "global_variable int with no intializer " << EQUALS_STRING(global_variable, int{}) << " int{}" << endl;
            
            WILL_NOT_COMPILE(
                cout << local_variable << endl; // local_variable is used without initialization
            );

            int* free_store_variable = new int; // free_store_variable is not initialized, TODO if class's constructor is to be called, wich it is? Default constructor, I guess, but why value is random with vc++17?
            cout << "free_store_variable int with no intializer " << EQUALS_STRING(*free_store_variable, int{}) << " int{}" << ", it is " << *free_store_variable << endl; // -842150451 with vc++17, 0 with mac os g++17. TODO why?
            delete free_store_variable;
        }
    }
}
