#include<iostream>
#include<complex>
#include <array>
#include"Utils.hpp"

using namespace std;

// identifier - /[_a-zA-Z$]([_0-9a-zA-Z$])*/, no keywords, no @, no $ (but vc++17 does not complain)
// names that starts with /__/ or /_[A-Z]/ are reserved, better not to use them

// user defined types: struct, class, union, enum, enum class

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
            void bar() {} // cannot declare non-global, non-class, non-struct function, use lambdas
        );

    } // global functions and namespaces need no trailing ;
} // global functions and namespaces need no trailing ;

int y = N::A::x;

// C++ offers two related meanings of ‘‘constant’’:
// • constexpr: Evaluate at compile time
// • const: Do not modify in this scope

int main() {
    // TODO declaration with definition
    // TODO Structure of declaration
    // TODO name -> left -> right rule of declaration reading
    // TODO examples of complex declarations
    // TODO const
    {
        string(name); // declaration of variable with name `name`;
        COMPILATION_ERROR(
            // Redefinition of 'name'
            string(name); // whenever compiler encounters an ambiguity between declaration and expression it chooses declaration
        )
        string{name}; // expression, call of constructor `std::string{const std::string&)`, temporary variable constructed
    }
    {
        int* name1; // pointer to an int, equivalent to int(*name)
        int(*name2); // pointer to an int, equivalent to int *name
        cout << "int* name is " << describe_type(typeid(name1).name()) << ", int(*name) is " << describe_type(typeid(name2).name()) << endl;
    }
    {
        int* x, y; // x is a pointer to an int, y is an int
        cout << "x is " << describe_type(typeid(x).name()) << ", y is " << describe_type(typeid(y).name()) << endl;
    }
    {
        int a[1], * b; // `a` is an array, `b` is a pointer
        cout << "a is " << describe_type(typeid(a).name()) << ", b is " << describe_type(typeid(b).name()) << endl;
    }
    {
        // if some construction looks like a declaration - it is!
        (int) (x); // it is not variable x of type int
        cout << "me: what are you, x? x: I am '" << describe_type(typeid(x).name()) << "' *troll_face*" << endl;
        // and... it is int...
        // TODO find confusion declaration with can be mentioned as constructor call but it is not
        COMPILATION_ERROR(
            int y(); // TODO why not?
        );
    }
    {
        // ATTENTION! In a declaration () - empty pair of parentheses always means "function".
        complex<double> z1(); // function? yeah :-)
        cout << "me: what are you, z1? z1: I am '" << describe_type(typeid(z1).name()) << "' *troll_face*" << endl;
        complex<double> z2{}; // complex with default values, as complex<double> z2;
        cout << "me: what are you, z2? z2: I am '" << describe_type(typeid(z2).name()) << endl;
    }
    {
        // Decomposition of aggregates, performed with `auto` and `auto&` only. `auto&&`?
        auto [x, y] = tuple { 13, 42 };
        cout << "[x, y] is [" << x << ", " << y << "]" << endl;

        COMPILATION_ERROR(
            // Cannot decompose private member '__begin_' of 'std::initializer_list<int>' implicitly declared private
            auto [x, y] = { 13, 42 };
        );

        struct the_pair {
            int x;
            int y;
        };
        auto [a, b] = the_pair{}; // It is a decomposition of aggregates

        COMPILATION_ERROR(
            //Decomposition declaration cannot be declared with type 'int'; declared type must be 'auto' or reference to 'auto'
            int [x, y] = the_pair{};
        )

        // arrays are aggregates
        int ar[2] = { 111, 222 };
        auto [xx, yy] = ar;
        cout << "decomposition of arrays: int ar[2] = {111, 222}, decomposed to xx=" << xx << ", yy=" << yy << endl;

        COMPILATION_ERROR(
            // Type 'int[2]' decomposes into 2 elements, but 3 names were provided
            auto [xxx, yyy, zzz] = ar;
        )
        int* ar_dynamic = new int[2];
        COMPILATION_ERROR(
            // Cannot decompose non-class, non-array type 'int *'
            auto [xxx, yyy, zzz] = ar_dynamic;
        )
        delete [] ar_dynamic;

        auto foo = [](int a[]) {
            // yet again, function "arrays" parameters are pointers
            COMPILATION_ERROR(
                // Cannot decompose non-class, non-array type 'int *'
                auto [x, y] = a;
            )
        };
        foo(ar);

        int size = 2;
        int the_a[size]; // compiler does not know size of `the_a`, `the_a` is a pointer.
        COMPILATION_ERROR(
            // Cannot decompose non-class, non-array type 'int *'
            auto [xxx, yyy] = the_a;
        )

        // shocked...
        COMPILATION_ERROR(
            // 'typeid' of variably modified type 'int[s]'
            cout << "type of `int the_a[size]` is " << describe_type(typeid(the_a).name()) << endl;
        )
        array<int, 3> std_ar = { 1, 2, 3 };
        // std::initializer_list is a structure with two field, whereas std::array... is an array...
        auto [xxx, yyy, zzz] = std_ar; // OK
    }
// const
    {
        // error because we cannot initialize value later (oh, yes we could, like in Java... but no)
        COMPILATION_ERROR(
            const int x; // default initialization of an object of const type 'const int'
            x = 2;
        );
    }
    {
        int x = 2;
        // if name is constexpr all initializing values must be constexpr or const
        COMPILATION_ERROR(
            constexpr y = x; // C++ requires a type specifier for all declarations 
        );
        constexpr int cex = 2; // literal are constexpr
        constexpr int y = cex; // ok, because of cex's constexpr
    }
    {
        const int x = 2;
        constexpr int y = x; // ok, because x is const, and can be evaluated at compile time

        int a = 1, b = 2;
        const int z = a + b;
        COMPILATION_ERROR(
            constexpr int n = z; // initializer of 'z' is not a constant expression, it depends on non-constant values
        );
    }
    {
        // const is an attribute of a name, not of an object it refers to
        const int a[2] = { 1, 2 }; // a[i] is a const int
        COMPILATION_ERROR(
            a[0] = 1; // Cannot assign to variable 'a' with const-qualified type 'const int [2]'
        );
        COMPILATION_ERROR(
            a = new int[3]; // neither we can do this: Cannot assign to variable 'a' with const-qualified type 'const int [2]' 
        );
    }
}
