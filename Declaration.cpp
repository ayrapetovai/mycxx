#include<iostream>
#include<complex>
#include"Utils.hpp"

using namespace std;

// identifier - /[_a-zA-Z$]([_0-9a-zA-Z$])*/, no keywords, no @, no $ (but vc++17 does not complain)
// names that starts with /__/ or /_[A-Z]/ are reserved, better not to use them

int x = 2; // global scope x

namespace N {
    class A {
        // class scope
    public:
        static const int x = 4; // x shedows ::x in class members
    };

    // naspace scope
    void foo() {
        // local scope
        {
            // local scope
        }
        if (int x = 1; x == 1) { // statement scope x, shedowing ::x
            // local scope
            ::x = 3; // accessing global scope x by namespace qualifier :: with no name - global
        }
        A::x; // x of class A

        COMPILATION_ERROR(
            void bar() {} // cannot declare non-global, non-class, non-struct fanction, use labdas
        );

    } // global functions and namespaces need no trailing ;
} // global functions and namespaces need no trailing ;

int y = N::A::x;

// C++ offers two related meanings of ‘‘constant’’:
// • constexpr: Evaluate at compile time
// • const: Do not modify in this scope

int main() {
    // TODO declaration with definition
    // TODO initialization
    // TODO Structure of declaration
    // TODO name -> left -> right rule of declaration reading
    // TODO examples of complex declarations
    // TODO const
    // TODO parensies role in reclaration
    // TODO describe type nameing acronims, i for int, template class naming etc.
    {
        int* name1; // pointer to an int, equivalent to int(*name)
        int(*name2); // pointer to an int, equivalent to int *name
        cout << "int* name is " << typeid(name1).name() << ", int(*name) is " << typeid(name2).name() << endl;
    }
    {
        int* x, y; // x is a pointer to an int, y is an int
        cout << "x is " << typeid(x).name() << ", y is " << typeid(y).name() << endl;
    }
    {
        int a[1], * b; // a is an array, b is a pointer
        cout << "a is " << typeid(a).name() << ", b is " << typeid(b).name() << endl;
    }
    {
        // if some construction looks like a declaration - it is!
        (int) (x); // it is not variable x of type int
        cout << "me: what are you, x? x: I am '" << typeid(x).name() << "' *troll_face*" << endl;
        // and... it is int...
        // TODO find confusin declaration with can be mentioned as constructor call but it is not
        COMPILATION_ERROR(
            int y(); // TODO why not?
        );
    }
    {
        // ATTENTION! In a declaration () - empty pair of parantheses always means "function".
        complex<double> z1(); // function? yeah :-)
        cout << "me: what are you, z1? z1: I am '" << typeid(z1).name() << "' *troll_face*" << endl;
        complex<double> z2{}; // complecx with default values, as complex<double> z2;
        cout << "me: what are you, z2? z2: I am '" << typeid(z2).name() << endl;
    }
    {
        // TODO what is the name of this feature? extraction? What is the grammar context in wich [] works? declaration with auto?
        auto [x, y] = tuple { 13, 42 };
        cout << "[x, u] is [" << x << ", " << y << "]" << endl;

        COMPILATION_ERROR(
            auto [x, y] = { 13, 42 }; // TODO why :,( it looks normal...
        );
    }
// const
    {
        // error becouse we cannot initialize value later (oh, yes we could, like in Java... but no)
        COMPILATION_ERROR(
            const int x; // default initialization of an object of const type 'const int'
        );
    }
    {
        int x = 2;
        // if name is constexpr all initializing values must be constexpr or const
        COMPILATION_ERROR(
            constexpr y = x; // C++ requires a type specifier for all declarations 
        );
        constexpr int cex = 2; // literal are constexprs
        constexpr int y = cex; // ok, becouse of cex's constexpr
    }
    {
        const int x = 2;
        constexpr int y = x; // ok, becouse x is const, and can be evaluated at compile time

        int a = 1, b = 2;
        const int z = a + b;
        COMPILATION_ERROR(
            constexpr int n = z; // initializer of 'z' is not a constant expression, it depends on non-constant values
        );
    }
    {
        // const is an attribute of a name, not of an object it referes to
        const int a[2] = { 1, 2 }; // a[i] is a const int
        COMPILATION_ERROR(
            a[0] = 1; // Cannot assign to variable 'a' with const-qualified type 'const int [2]'
        );
        COMPILATION_ERROR(
            a = new int[3]; // neither we can do this: Cannot assign to variable 'a' with const-qualified type 'const int [2]' 
        );
    }
}
