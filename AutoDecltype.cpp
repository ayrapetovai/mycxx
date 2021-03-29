#include<iostream>
#include<complex>
#include"Utils.hpp"

using namespace std;

// C++ has two mechanisms for deducing a type from expression:
//    1. auto deduces type from initializer, decltype(expr)
//    2. decltype(expr) deduces type from complex expression
// auto and decltype simply report the type already knowen to the compiler

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

// example from the book (6.3.6.3, page 165) does not work with vc++17, but it works in clang
#ifndef _WIN32
    template<class T, class U>
    auto operator+(const complex<T>& a, const complex<U>& b)->complex<decltype(T{} + U{}) > {
        return complex<decltype(T{} + U{})>{ a.real() + b.real(), a.imag() + b.imag() };
    }
#endif

int main() {
    // ACHTUNG!!!
    // auto never reduces reference type implicitly, write explicit & to make aout to deduce a reference type (auto& ref = x) [thas is 100% shure]
    // same thing for const? [not shure]

    cout << typeid(decltype(1 + 1)).name() << endl;
    cout << "A::bar auto is " << typeid(A::bar).name() << ", B::bar auto is " << typeid(B::bar).name() << endl;
    {
        const int x = 7;
        auto y = x;
        cout << "spesifiers of y? " << typeid(y).name() << endl; // no const! Only int!
    }
    {
        // TODO what is the rule of deducing?
        const int x = 7;
        auto y = &x;
        cout << "spesifiers of y? " << typeid(y).name() << endl; // now it y is " int const * "
    }
    {
        COMPILATION_ERROR(
            auto lst{}; // cannot deduce type, lst channot be initializer_list<?>
        );
        auto list{ 1 };// TODO Stroustrup (6.3.6.2, page 165), says "list" should be initializer_list, but it is int with cv++17
        cout << "typeof(auto list{1}) " << EQUALS_STRING(typeid(list), typeid(int)) << " int" << endl;

        COMPILATION_ERROR(
            auto lst{ 1, 2, 3 }; // TODO Stroustrup (6.3.6.2, page 165), says it must work (list of three elemnts), but with cv++17 - no...
        )
        {
            // deltype is to be used when type of an expression must be computed
#ifndef _WIN32
                auto sum = complex<int>{ 1, 1 } + complex<double>{ 1.0, 1.0 };
                cout << "complex sum type is " << typeid(sum).name() << endl;
#endif
        }
    }
}
