#include<iostream>
#include <array>
#include "Utils.hpp"

using namespace std;

int foo() {
    cout << " `foo()`";
    return 2;
}

int bar() {
    cout << " `bar()`";
    return 3;
}

void foo(int) {}
void foo(int, int) {}

constexpr int isqrt_helper (int sq, int d, int a) {
    return sq <= a ? isqrt_helper(sq+d,d+2,a) : d;
}

constexpr int isqrt(int x) {
    return isqrt_helper(1,3,x)/2 - 1;
}

// TODO Operator Precedence
int main() {
    {
        cout << "Order of calls foo and bar `x = foo() + bar()`: ";
        int x = foo() + bar(); // order is no defined
        cout << ". Result is " << x << endl;
    }
    {
        foo(3, 4);   // foo(int, int)
        foo((3, 4)); // foo(int) <- 4, because of `,` operator
    }
    {
        int x = -10;
        if (0 <= x <= 99) { // compile, but is (0<=x)<=99
            cout << "0 <= x <= 99 is bad" << endl;
        }

        if (x = 2) {
            cout << "if (x = 2) disaster" << endl;
        }
    }
    {
        string s1 = "abc";
        string s2 = "dfg";
        const char* cs = (s1+s2).c_str();
        // temporary variable of type `string` that is a result of concatenation of `s1` and `s2`
        // was destroyed (memory freed) after assignment to `cs` the result of evaluation of the expression `(s1+s2).c_str()`
        // now `cs` points to deallocated memory...
        UNDEFINED_BEHAVIOR(
            cout << cs << endl;
        )
        const string& s = (s1+s2); // ok, materialization of temporary variable
        cs = s.c_str();
        cout << "content of materialized string is \"" << cs << "\"" << endl;

        // OK, `cs` points to allocated memory in temporary variable
        // that exist while condition expression is evaluated
        if (strlen(cs=(s1+s2).c_str())<8 && cs[0]=='a') {
            // here `cs` is not touched
        }
    }
    {
        // evaluation of `constexpr` functions with recursion can be done in compile time
        // `isqrt` uses recursive `isqrt_helper`.
        constexpr int sqrt1234 = isqrt(1234);
        cout << "sqrt1234 = " << sqrt1234 << endl;
    }
    {
        // In order to be eligible for `constexpr` expressions object
        // must be of `literal type`.
        // `literal type` - class is a constexpr constructor, arithmetic type (char, int..., float, ...) or enum.
        struct Point {
            int x; int y;
            constexpr Point(int x, int y): x(x), y(y) {}
            constexpr Point move(int dx, int dy) const { return {x+dx,y+dy}; }
        };

        // compile error, if `constexpr Point(int x, int y)` would have no `constexpr`
        constexpr array<Point, 2> loc = { Point{1, 2}, Point{3, 4}.move(1, 1)};
    }
    {
        // compiler can operate on addresses of constexpr values in compile time
        constexpr const char* p1 = "asdf";
        constexpr const char* p2 = p1+2;
        constexpr char c = p1[2];
        cout << R"(given constexpr pointer to "asdf": print p+2 ")" << p2 << R"(", print p[2] ")" << c << R"(")" << endl;

        // compiler can not operate on addresses of const values in compile time
        const int i = 142;
        COMPILATION_ERROR(
            // Constexpr variable 'pi' must be initialized by a constant expression pointer to 'i' is not a constant expression
            constexpr const int* pi = &i;
        )
    }
    {
        // "narrowing conversion" - when value being converted to some type cannot be converted back without loose of information
        // non-narrowing implicit conversions are "promotions".

        // "integral promotion" - before each operation on integral type values each of them it promoted to `int`,
        // unless values are of type wider than `int`
        char a = 2, b = 3;
        cout << "type of (char + char) is " << describe_type(typeid(a + b).name()) << endl; // prints "int"
        // "promotions" is done to the widest type of ether values

        char ca = 2;
        unsigned char ucb = 3;
        cout << "type of (char + unsigned char) is " << describe_type(typeid(ca + ucb).name()) << endl; // prints "int"

        int ia = -1;
        unsigned int uib = 3;
        cout << "type of (int + unsigned int) is " << describe_type(typeid(ia + uib).name()) << ", addition result is " << (ia + uib) << endl;
        // prints "unsigned int, addition result is 2"
        cout << "type of (int * unsigned int) is " << describe_type(typeid(ia * uib).name()) << ", addition result is " << (ia * uib) << endl;
        // prints "unsigned int, addition result is 4294967293"

        char a1 = 2;
        long b1 = 3;
        cout << "type of (char + long) is " << describe_type(typeid(a1 + b1).name()) << endl; // prints "long"
        long x = 2, y = 3;
        cout << "type of (long + long) is " << describe_type(typeid(x + y).name()) << endl; // prints "long"

        // Mr. Stroustrup: "floating-point promotion" - same for `float` - promoted to `double`,
        // but these variables are not promoted! (Apple clang)
        float f1 = 1.0, f2 = 4.0;
        cout << "type of (float + float) is " << describe_type(typeid(f1 + f2).name()) << endl; // prints "float"

        // `bool` promotes to `int`
        bool ba = true, bb = false;
        cout << "type of (bool + bool) is " << describe_type(typeid(ba + bb).name()) << endl; // prints "int"
    }
    {
        // implicit narrowing
        signed char sc = 1023; // implementation-defined
        // possible values of `sc` are 127 and -1.
        cout << "narrowing 0xFF to unsigned char gives " << int(sc) << endl; // prints "-1" on MacOS intel
    }
    {
        // pointer-to-bool conversion
        int x;
        int *px = &x;
        COMPILATION_ERROR(
            // Type 'int *' cannot be narrowed to 'bool' in initializer list
            bool b { px };
        )
        auto foo = [](bool b) {};
        foo(px); // OK, but bad

        if (px) {
            // OK, and not bad?
        }
    }
    {
        // conditional expression
        // c ? a: b;
        // ok, if decltype(a) == decltype(b) and cant be implicitly converted to decltype(c)
        int x = 1;
        char y = 2;
        bool b = false;
        char c1 = b? x: y; // implicit narrowing

        COMPILATION_ERROR(
            // Non-constant-expression cannot be narrowed from type 'int' to 'char' in initializer list
            char c2 { b? x: y }; // `{}` initializer forbids implicit narrowing
        )
        int c2 { b? x: y }; // no implicit narrowing
    }
    {
        // Increment and Decrement
        int x = 0, xx = 0, y, yy, t;

        y = ++x;
        // equivalent to
        yy = (xx = xx + 1);

        cout << "x=" << x << "; y = ++x; y==" << y << "; x==" << x << endl;
        cout << "x=" << xx << "; y = (x = x + 1); y==" << yy << "; x==" << xx << endl;

        x = 0;
        xx = 0;
        y = x++;
        // equivalent to
        yy = (t = xx, xx = xx + 1, t);

        cout << "x=" << x << "; y = x++; y==" << y << "; x==" << x << endl;
        cout << "x=" << xx << "; y = (t = xx, xx = xx + 1, t); y==" << yy << "; x==" << xx << endl;
    }
    {
        // `a?:b` is `a? a: b`, where `a` is evaluated one time
        string s = "123"?:"abc";
        int x = 17?:23;

        int *p = nullptr;
        RUNTIME_ERROR(
            auto pi = *p?:213; // interrupted by signal 11: SIGSEGV
        )

        const auto pi = p ?: &x;
        cout << s << " " << x << " " << *pi << endl;
        // prints "123 17 17"
    }
}