#include<iostream>
#include<complex>
#include"Utils.hpp"

using namespace std;

// C++ has two mechanisms for deducing a type from expression:
//    1. auto deduces type from initializer, decltype(expr)
//    2. decltype(expr) deduces type from complex expression
// auto and decltype simply report the type already known to the compiler

// auto decays:
// - raw arrays converted to pointers
// - functions converted to function pointers
// - top-level references are removed
// - top-level const/volatile qualifiers are removed
// as passing arguments by value.

int a_var_for_type_deducing;

decltype(a_var_for_type_deducing) foo() {
    // if decltype() is used in declaration we can use it as such it was a typename
    return a_var_for_type_deducing;
}
namespace A {
    // auto deduces " char const * "
    auto bar() {
        return "";
    }
}
namespace B {
    // auto deduces std::string
    auto bar() {
        return ""s;
    }
}

// example from the book (6.3.6.3, page 165)
template<class T, class U>
auto operator+(const complex<T>& a, const complex<U>& b)->complex<decltype(T{} + U{}) > {
    return complex<decltype(T{} + U{})>{ a.real() + b.real(), a.imag() + b.imag() };
}


int main() {
    // ACHTUNG!!!
    // auto never reduces reference type implicitly,
    // write explicit & to make auto to deduce a reference type (auto& ref = x) [that is 100% sure]
    // same thing for const? [not sure]

    cout << "type of `decltype(1 + 1)` is `" << describe_type(typeid(decltype(1 + 1)).name()) << "`" << endl;
    cout << "A::bar auto is `" << describe_type(typeid(A::bar).name()) << "`, B::bar auto is `" << typeid(B::bar).name() << "`" << endl;
    {
        const int x = 7;
        auto y = x; // auto decay - top-level const/volatile qualifiers are removed, `y` is a new object!
        cout << "auto y = x of (const int x), specifiers of y: " << describe_type(typeid(y).name()) << ", from x: " << describe_type(
                typeid(x).name()) << endl; // no const! Only int!
    }
    {
        int const x = 7;
        auto y = x; // auto decay - top-level const/volatile qualifiers are removed, `y` is a new object!
        cout << "auto y = x of (int const x), specifiers of y: " << describe_type(typeid(y).name()) << ", from x: " << describe_type(
                typeid(x).name()) << endl; // now it y is "int"
    }
    {
        const int x = 7;
        auto y = &x; // auto decay - top-level references are removed
        cout << "auto y = &x of (const int x), specifiers of y: " << describe_type(typeid(y).name()) << endl; // now it y is " int const * "
    }
    {
        // there `const` is a "top-level" modifier.
        int* const x = nullptr;
        auto y = x; // auto decay - top-level const/volatile qualifiers are removed
        cout << "auto y = x of (int* const x), specifiers of y: " << describe_type(typeid(y).name()) << endl; // now it y is "int*"
    }
    {
        const int* x = nullptr;
        auto y = x; // no "auto decay" happened.
        cout << "auto y = x of (const int* x), specifiers of y: " << describe_type(typeid(y).name()) << endl; // now it y is "const int*"
    }
    {
        int z = 1;
        int& x = z; // `x` is not a new object, it is a reference to `z`.
        auto y = x; // auto decay - top-level references are removed, `y` is a new object!
        cout << "auto y = x of (int& x), specifiers of y: " << describe_type(typeid(y).name()) << endl; // y is int
    }
    {
        int x = 1;
        auto& y = x; // no auto decay, `y` is not a new object, it is a reference to the old object `x`;
        x = 2;
        cout << "auto& y = x of (int x), specifiers of y: " << describe_type(typeid(y).name()) << ". x := 2, did `y` changed, " << YESNO_STRING(y == 2)  << "!" << endl; // y is int&
        // TODO somehow `typeid(y).name()` returns "i"... but is obvious, that `y` is a reference! Where is the problem?
        //  if `int& x = ...` then `typeid(x).name()` also returns "i"...
        //  Same for auto&&.
    }
    {
        int x = 1;
        auto&& y = x; // auto decay, top-level references are removed, but `y` is not a new object, it is a reference to the old object `x`;
        x = 2;
        cout << "auto&& y = x of (int x), specifiers of y: " << describe_type(typeid(y).name()) << ". x := 2, did `y` changed, " << YESNO_STRING(y == 2)  << "!" << endl; // y is int&
    }
    {
        char x[] = {'a', 'b', 'c'};
        auto y = x; // auto decay - raw arrays converted to pointers
        cout << "auto y = x of (char x[]), specifiers of y: " << describe_type(typeid(y).name()) << endl; // y is char*
    }
    {
        COMPILATION_ERROR(
            auto lst{}; // cannot deduce type, lst cannot be initializer_list<?>
        );
        auto list{ 1 };// TODO Stroustrup (6.3.6.2, page 165), says "list" should be initializer_list, but it is int with cv++17
        cout << "typeof(auto list{1}) " << EQUALS_STRING(typeid(list), typeid(int)) << " int" << endl;

        COMPILATION_ERROR(
            auto lst{ 1, 2, 3 }; // TODO Stroustrup (6.3.6.2, page 165), says it must work (list of three elements), but with cv++17 - no...
        )
        {
            // `decltype` is to be used when type of expression must be computed
            auto sum = complex<int>{ 1, 1 } + complex<double>{ 1.1, 1.3 };
            cout << "complex sum type is " << describe_type(typeid(sum).name()) << ", value is " << sum << endl;
        }
    }
}
