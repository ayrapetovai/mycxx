#include<iostream>
#include <vector>
#include <complex>
#include <array>
#include "Utils.hpp"

using namespace std;

// source https://github.com/MicrosoftDocs/cpp-docs/blob/main/docs/cpp/initializers.md
// direct initialization - initial value passed directly.
// copy initialization - initialization with `=`, not possible with `explicit`, c++17 relaxes it.
// default initialization - object is initialized only is corresponding constructor is defined.
// zero initialization - object initialized by (converted) 0, used for static/global/thread-local objects.
// value initialization - object always gets the value (initialized by constructor or zero initialized).
// list initialization - object is initialized by braces (both direct-list-initialization or copy-list-initialization).
// aggregate initialization - special form of list initialization is type is aggregate (structs, arrays, types of multiple members, not unions). std::is_aggregate_v<T>
// reference initialization - initializing a reference-type variable, the compiler selects between creating a reference to an object or creating a temporary object to which the reference points.

// Aggregate structure (c++20):
// - no user-provided, explicit, or inherited constructors,
// - no private or protected non-static data members, - no virtual, private, or protected base classes, and
// - no virtual functions

// "Use `{...}` for all initializations. Don't use `=` in initializations." (c) Nicolai Josuttis
// "Use AAA rule: Almost Always Auto." (c) Nicolai Josuttis
// Because of auto decay "Use AAAA rule: Always Auto Ampersand Ampersand?" (c) Nicolai Josuttis
// syntax `auto x = T()` works only for types that are copyable or movable.

// if no initializer specified then:
// global, namespace, local static and static (collectively called static objects) is initialized to {} - default initializer

// copy-initialization syntax:
// T object = other;
// f(other)
// return other;
// throw object;
// catch (T object)
// T array[N] = {other-sequence};

int global_variable; // zero initialization
extern int extern_global_variable; // no initialization, `extern_global_variable` is `extern` it meant to be initialized in other compilation unit;

void the_func(initializer_list<int> list) {
    cout << "the_func(initializer_list<int> list) is called, args: x=" << *list.begin() << ", y=" << *(list.begin() + 1) << endl;
}

int main() {
    cout << boolalpha;
    {
        // initializer_list object is created when passed to function call
        // the underlying array is a temporary array of type `const T[N]`,
        // in which each element is copy-initialized
        the_func({1, 2});
    }
    {
        // initializer syntax
        int x_1;        // undefined value, not initialized, can be anything
        int x0{};       // zero initialization
        int x1{ 1 };    // direct initialization
        int x2 = { 2 }; // use constructor; list initialization
        int x3 = 3;     // copy initialization
        int x4(4);      // direct initialization
        cout << "x[i] in (" << x_1 << ", " << x0 << ", " << x1 << ", " << x2 << ", " << x3 << ", " << x4 << ")" << endl;

        int x5 = (5, 6); // x5 initialized with 6 as a result of evaluation of expression with is comma-expr-list
        cout << "int x = (5, 6) is " << x5 << endl;

        int x6(); // declares a function
    }
    {
        // aggregate initialization
        int ar1[] = {1, 2, 3};
        int ar2[] {1 , 2, 3};
        vector<string> cities{"Moscow", "Minsk", "Astana"};
        // outputs "Moscow, Minsk, Astana, "
        copy(cities.begin(), cities.end(), ostream_iterator<string>(cout, ", "));
        cout << endl;
        // TODO why ostream_iterator implemented to print delimiter after last element?
    }
    {
        // list initialization {} does not allow narrowing - when initial value has to be truncated
        COMPILATION_ERROR(
            short x{ 1000000 }; // compilation error: 1000000 requires truncating
        );
        short x_short{ (short)1000000 }; // ok: (sort) 1000000 is truncated explicitly

        // compilation error: type 'float' cannot be narrowed to 'int' in initializer list [-Wc++11-narrowing]
        COMPILATION_ERROR(
            int x{ 0.0f }; // float|double -/-> int|short|long
        );

        double xx{ 1 }; // int|short|long ---> float|double

        float xxx{ 0.0 }; // here, 0.0 is double, double ---> float
    }
    {
        class ChooseConstructor {
        public:
            ChooseConstructor(int i = 1) {
                cout << "call ChooseConstructor(int)" << endl;
            }
            ChooseConstructor(initializer_list<int> list) {
                cout << "call ChooseConstructor(initializer_list<int>)" << endl;
            };
        };
        // non-empty `{...}` always call constructor with initializer_list
        ChooseConstructor x0(1); // `()` never calls initializer_list constructor, ChooseConstructor(int)
        ChooseConstructor x1{};     // empty initializer list, calls ChooseConstructor(int) because we have it
        ChooseConstructor x2{2};    // calls ChooseConstructor(initializer_list<int>)
        ChooseConstructor x3{3, 4}; // calls ChooseConstructor(initializer_list<int>)
    }
    {
        vector<int> v1(3, 42); // [42, 42, 42]
        vector<int> v2{3, 42}; // [3, 42]
        vector<int> v3 = {42, 42}; // [42, 42]
    }
    {
        // Stroustrup says: z is an initializer_list<int>, but it is int in vc++17 and it is int in clang.
        auto z1{ 99 };
        cout << "auto z1{ 99 } is " << typeid(z1).name() << endl; // int
        // I like z to be int in this syntax...

        auto z2 = { 99 };
        cout << "auto z2 = { 99 } is " << typeid(z2).name() << endl; // St16initializer_listIiE

        auto z3 = int{ 99 };
        cout << "auto z3 = int{ 99 } is " << typeid(z3).name() << endl; // int
    }
    {
        int x{}; // zero initialization
        cout << "int x{} " << EQUALS_STRING(x, int(0)) << " int(0), or 0, or int()" << endl;
    }
    {
        int* pi{}; // zero initialization
        cout << "int *pi{} " << EQUALS_STRING(pi, nullptr) << " nullptr, int *pi{} " << EQUALS_STRING(pi, NULL) << " NULL, int *pi{} " << EQUALS_STRING(pi, 0) << " 0" <<  endl;
    }
    // TODO constructors, https://en.cppreference.com/w/cpp/language/value_category, deleted constructors, move
    {
        auto is_zero = [](char byte){ return byte == 0; };

        // buffer_size variable does not exist in runtime, it does not occupy automatic memory
        constexpr int buffer_size = 120; // calculated at compile time
        char buf1[buffer_size]{};    // zero initialization: buf1 is arrays of buffer_size chars initialized with 0
        bool all_zeroes1 = all_of(buf1, buf1+buffer_size, is_zero);
        cout << "in char buf1[buffer_size]{} all elements are 0: " << YESNO_STRING(all_zeroes1) << endl;

        char buf2[buffer_size] = {}; // copy list initialization: buf2 is arrays of buffer_size chars initialized with 0
        bool all_zeroes2 = all_of(buf2, buf2+buffer_size, is_zero);
        cout << "in char buf2[buffer_size] = {} all elements are 0: " << YESNO_STRING(all_zeroes2) << endl;
    }
    {
        // global_variable is defined at the begining
#pragma warning(suppress: 4101) // unused local variable
        int local_variable;
        cout << "global_variable int with no intializer " << EQUALS_STRING(global_variable, int{}) << " int{}" << endl;
        
        COMPILATION_ERROR(
            cout << local_variable << endl; // local_variable is used without initialization
        );

        int* free_store_variable = new int; // free_store_variable is not initialized
        // TODO if class's constructor is to be called, wich it is?
        // Default constructor, I guess, but why value is random with vc++17?

#pragma warning(suppress: 6001) // using uninitialized memory, with vc++17
        cout << "free_store_variable int with no intializer " << EQUALS_STRING(*free_store_variable, int{}) << " int{}";
        cout  << ", it is " << *free_store_variable << endl; // -842150451 with vc++17, 0 with mac os clang++17. TODO why?
        delete free_store_variable;
    }
    {
        // construct object with a constructor
        struct Explicit {
            Explicit() {
                cout << "call Explicit() ";
            }
            ~Explicit() {
                cout << "call ~Explicit() ";
            }
        };
        {
            cout << "e = Explicit() : ";
            Explicit e = Explicit(); // constructor call
        }
        {
            cout << endl;
            cout << "e() : function declaration no object constructed";
            Explicit e(); // Empty parentheses interpreted as a function declaration 
            cout << endl;
        }
        {
            cout << "e{} : ";
            Explicit e{}; // Explicit() constructor call
        }
        cout << endl;
    }
    {
        // AAA
        string s1 = "abc";
        // do
        auto s2 = "def"s; // s2 is `std::string`, `s` is a globally available postfix operator
        // but
        auto s3 = "ghi"; // s3 is `const chat*`
        cout << "the s[i]: " << s1 << ", " << s2 << ", " << s3 << endl;
    }
    {
        // Copy elision for initialization for temporary (prvalue) is required
        // Callable copy/move constructors not required.
        class NoCopyAndMove {
        public:
            NoCopyAndMove() {
                cout << "call NoCopyAndMove()" << endl;
            };
            // no copy/move constructors
            NoCopyAndMove(const NoCopyAndMove&) = delete;
            NoCopyAndMove(NoCopyAndMove&&) = delete;
        };

        cout << "example of copy elision for passing by value:" << endl;
        auto foo = [](NoCopyAndMove obj) {};
        // only one call of NoCopyAndMove() will be done
        foo(NoCopyAndMove()); // passing prvalue by value (no coping, no constructing, no moving), OK.

        cout << "example of copy elision for returning by value:" << endl;
        auto bar = []() { return NoCopyAndMove(); };
        // only one call of NoCopyAndMove() will be done
        auto obj = bar(); // getting prvalue from function (no coping, no constructing, no moving), OK.

        cout << "example of copy elision for returning and passing by value:" << endl;
        // only one call of NoCopyAndMove() will be done
        foo(bar());

        cout << "example of copy elision for materialization:" << endl;
        // only one call of NoCopyAndMove() will be done
        // prvalue --materialization--> xvalue - temporary materialization conversion
        const NoCopyAndMove& ref = bar(); // NoCopyAndMove's instance "materialises" after `bar` called.

        COMPILATION_ERROR(
            auto inited_obj = NoCopyAndMove();
            // Object of type 'NoCopyAndMove' cannot be assigned because its copy assignment operator is implicitly deleted
            inited_obj = bar(); // compilation error is here, in `=` - copy semantics
        );
    }
    {
        // Constructors and type conversion operators define implicit conversions, `explicit` disables implicit conversions:
        class Collection {
        public:
            explicit Collection(int size) {}
        };
        auto foo = [](const Collection&) {};

        // No matching function for call to object of type (would be OK without `explicit` in Collection(int))
        COMPILATION_ERROR(
            foo(1);
            Collection c1 = 1;
            Collection c2 = {2};
        )
        foo(Collection(1));
        foo(Collection{1});
    }
    {
        class Collection {
        public:
            Collection(int size) {}
            explicit Collection(initializer_list<int>) {}
        };
        auto foo = [](const Collection&) {};

        foo(1);
        Collection c1 = 1;
        COMPILATION_ERROR(
            Collection c2 = {2}; // Chosen constructor is explicit in copy-initialization
        )
        Collection c3 = Collection{2}; // Ok, call Collection(initializer_list<int>)
        foo(Collection(1));
        foo(Collection{1});
    }
    {
        struct User {
            string name;
            bool registered;
        };
        struct Admin: User {
            int duty;
        };

        Admin admin = {{"Jon", true}, 23}; // aggregate initialization, error if Admin/User were `class`es.
        cout << "Admin is {" << "name=" << admin.name << ", registered=" << admin.registered << ", duty=" << admin.duty << "}" << endl;
        // outputs Admin is {name=Jon, registered=true, duty=23}

        COMPILATION_ERROR(
                // members of super class must be set first
            Admin admin = {23, {"Jon", true}};
        )
        // Also OK
        Admin admin2 = {"Jon", true, 23}; // aggregate initialization

        array<complex<int>, 3> ac = {{{1, 2}, {3, 4}, {5, 6}}}; // aggregate initialization, requires additional `{}`, because `array` struct has a `raw array` of `complex` inside.
        // compare to
        vector<complex<int>> vc = {{1, 2}, {3, 4}, {5, 6}}; // copy list initialization
    }
    {
        // reference initialization: volatile
        volatile int x;
        COMPILATION_ERROR(
            // Binding reference of type 'int' to value of type 'volatile int' drops 'volatile' qualifier
            int& y1 = x;
            const int& y2 = x;
        )
        volatile int& y = x; // OK
    }
    {
        // reference initialization: const
        const int x = 2;
        COMPILATION_ERROR(
            int& y = x; // Binding reference of type 'int' to value of type 'const int' drops 'const' qualifier
        )
        const int& y = x; // OK

        int x2;
        const int& y2 = x2; // OK

        COMPILATION_ERROR(
            y2 = 2; // Cannot assign to variable 'y2' with const-qualified type 'const int &'
        )
    }
    {
        int x;
        int& y = x;
        int& z = y;
        cout << "z is ref to y, y is ref to int, what is z? " << describe_type(typeid(z).name()) << endl;

        COMPILATION_ERROR(
            const int& p = &x; // Reference to type 'const int' could not bind to an rvalue of type 'int *'
        )
    }
}

