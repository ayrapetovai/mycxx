#include <cassert>
#include <iostream>
#include <array>
#include "Utils.hpp"

using namespace std;
// literal-tyep - class/struct with constexpr constructor: empty body, all memnbers can be initialized with constant expressions
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

struct Int1 {
    int value;
    ~Int1() {
        cout << "~Int1[value = " << value << "]" << endl;
    }
};

struct Int2 {
    int value;
    ~Int2() {
        cout << "~Int2[value = " << value << "]" << endl;
    }
};


Int2 operator+(const Int2& a, const int& b) {
    return Int2{ a.value + b };
}

Int2 operator+(const Int2& a, const Int1& b) {
    return Int2{ a.value + b.value };
}

Int2 operator+(const Int2& a, const Int2& b) {
    return Int2{ a.value + b.value };
}

struct Tmp {
    int *value;
    Tmp(const int& v): value(new int{v}) {
    }
    ~Tmp() {
        cout << "~Tmp(" << *value << ")" << endl;
        delete value;
    }
};
Tmp operator+(const Tmp& a, const Tmp& b) {
    return Tmp{*a.value + *b.value };
}
// function may be declared as constexpr
constexpr int returnsTen() {
    return 10;
}

constexpr int plusTen(int x) {
    // Non-constexpr function 'operator<<<std::__1::char_traits<char>>' cannot be used in a constant expression
    COMPILATION_ERROR(
        cout << "constexpr plusTen is called" << endl;
    );
    return x + 10;
}

int main() {
    {
        // Three-way comparison operator `<=>`: Java compareTo
        int x = 3;
        int y = 10;
        cout << "(3 <=> 10) type is " << describe_type(typeid(x <=> y).name()) << endl;
        cout << "(3 <=> 10) is less? " << (x <=> y == strong_ordering::less) << endl;
        // outputs "std::__1::strong_ordering" witch is `std::strong_ordering`
    }
    {
        double a = 32.23;
        double b = 42.123;
        cout << "(a <=> b) < 0: " << YESNO_STRING((a <=> b) < 0) << endl;

        auto nan_twc_double = numeric_limits<double>::quiet_NaN() <=> b;
        cout << "(NaN <=> b) ";
        if (nan_twc_double < 0) {
            cout << "< 0";
        } else if (nan_twc_double > 0) {
            cout << "> 0";
        } else if (nan_twc_double == 0) {
            cout << "== 0";
        } else {
            cout << "<> 0";
        }
        cout << ", real value is "<< *reinterpret_cast<int*>(&nan_twc_double) << endl;
        assert(nan_twc_double == partial_ordering::unordered);
        // prints "(NaN <=> b) <> 0" - unordered

        auto pz_nz_o = -0 <=> +0;
        assert(pz_nz_o == partial_ordering::equivalent);
        assert(pz_nz_o != partial_ordering::unordered);
    }
    {
        // order of evaluation is undefined
        cout << "x=foo(1) + bar(2) ";
        int x = foo(1) + bar(2);
        cout << endl;
    }
    {
        // order of evaluation is undefined: foo(bar()) or wah(baz())
        cout << "x=foo(bar(1)) + wah(baz(2)) ";
        int x = foo(bar(1)) + wah(baz(2));
        cout << endl;
    }
    {
        // order of evaluation is undefined
        array<int, 2> a = { 13, 42 };
        int i = 0;
        a[i] = i++; // undefined, Unsequenced modification and access to 'i'
        //    (   ) <- expressions boundaries

        cout << "array is [" << a[0] << ", " << a[1] << "]; i is " << i << endl; // [13, 0] 1
    }
    {
        // evaluation order of function arguments is undefined
        cout << "biconsumer(foo(1), bar(2) ";
        biconsumer(foo(1), bar(2));
        cout << endl;
    }
    {
        // A temporary object is destroyed at the end of the full expression in which it was created.
        // A full expression is an expression that is not a subexpression of some other expression.
        // TODO is this example correct? demonstrative?
        Int2 a{ 3 };
        Int1 b{ 5 };
        Int2 c{ 7 };
        Int2 d = a + b + 11 + c;
        // destruction is made in reversed order compare to create order
        // ~Int2[value = 19]   <-- temporary object  a + b + 3
        // ~Int2[value = 8]   <-- temporary object, a + b
        // ~Int2[value = 26]  <-- d
        // ~Int2[value = 7]   <-- c
        // ~Int1[value = 5]   <-- b
        // ~Int2[value = 3]   <-- a
    }
    {
        // access to memory left from temporary object is undefined behaviour
        Tmp a{ 1 };
        Tmp b{ 2 };
        int* pv = (a + b).value; // storage is not guaranteed to exist after that temporary is destroyed.
        // (a + b) object is destroyed after accessing by .value field (out of expression scope)
        // now pv points to deallocated storage
        cout << "value from remporary object is " << *pv << endl; // 3, however we can see it...
        // a and b are destroyed here
    }
    {
        // initializer of constexpr item must be evaluated at compile-time
        int x = returnsTen(); // constexpr int returnsTen()
        int y = plusTen(x);   // constexpr int plusTen(int)
        cout << "constexpr y = plusTen(x) is " << y << endl; // 20

        COMPILATION_ERROR(
            constexpr int z = x + y; // TODO why error: Constexpr variable 'z' must be initialized by a constant expression,
            // while plusTen takes non-constexpr x and works!
        );

        constexpr int cex = returnsTen();
        constexpr int z = cex; // ok, x is constexpr
    }
    {
        // code elemination on compile time
        if constexpr (true) {
            cout << "this code will be pasted to the binary executable" << endl;;
        } else {
            cout << "this code will no be pasted" << endl;
        }
    }
    {
        // constexpr item can be initialized only with constepsr expression or const item
        const int x = 1;
        const string s = "asd";

        constexpr int cex = x; // OK

        // consexpr can be only 'literal type' (a class with a constexpr constructor e. g. POD)
        COMPILATION_ERROR(
            constexpr string ces = s; // Constexpr variable cannot have non-literal type 'const std::__1::string' 
        );
    }
    {
        // Constexpr variable 'x' must be initialized by a constant expression
        COMPILATION_ERROR(
            constexpr int x = foo(1); // non-constexpr int foo(int)
        );

        const int x = foo(1);
        COMPILATION_ERROR(
            constexpr int y = x; // Constexpr variable 'y' must be initialized by a constant expression
        );
    }
    {
        // POD constexpr
        struct The_pod {
            int x;
            constexpr The_pod get_pod() const { return The_pod(); } // const makes 'this' to be const
            void operator=(const The_pod& other) const {}
        };

        constexpr The_pod p{1};
        constexpr The_pod pp = p.get_pod(); // OK
        pp = The_pod(); // operator= must be const for this to compile
    }
    {
        // Point is a literal-type, it can be initialized with potentialy constant expressions
        struct Point { int x; int y; };
        constexpr Point p{ 0, 0};
        constexpr int x = p.x;

        constexpr Point points[] = { Point{ 1, 1}, {0, 0} };
        constexpr auto pp = Point{ 1, 2 };
    }
}
