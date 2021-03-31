#include<iostream>
#include"Utils.hpp"

using namespace std;

// lvalue and rvalue
// lvalue (left value):
//      (has identity) the program has name, pointer to or a reference to an object,
//      (movable) we can copy object an leave it in undefined but valid state.
// rvalue (right value):
//      temporary object, has no identity.
// prvalue (pure right value):
// glvalue (generalized left value):
// xvalue (extraordinary value):
//
// Using 'i' for "has identity" and m for "moveable".
// the book (6.4.1)
//                         ___ value ___
//                        /             \
//                       /               \
//                 gvalue {i}        rvalue {m}
//               /            \    /            \
//              /              \  /              \
//       lvalue {i&!m}     xvalue {i&m}     prvalue {!i&m}

// "object has an identity" means: the object resides at a specific address in memory, and it can be accessed if you know its address and its type.
// In a type name notation X& means "reference to X", it is "lvalue reference"
// In type name notation X&& means "temporary object of type X", you can "steal" it's fields as they are without copy, it does not need them.

// Mr. Stroustrup: Use rvalue references only for forwarding and move semantics.

class Verbose {
    private:
        int _id = 0;
    public:
        Verbose(int id) {
            cout << "Verbose(int id): " << id << endl;
            _id = id;
        }
        // copy constructor, meant to do deep copy
        Verbose(const Verbose& other) {
            cout << "Verbose(const Verbose& other): " << other._id << " -> " << _id << endl;
            _id = other._id;
        }
        // move constructor, meant to do light copy
        Verbose(Verbose&& other) {
            cout << "Verbose(Verbose&& other): " << other._id << " -> " << _id << endl;
            _id = other._id;
        }
        ~Verbose() {
            cout << "~Verbose(): " << _id  << endl;
        }
        Verbose& operator=(const Verbose& other) {
            cout << "operator=(const Verbose& other): " << other._id << " -> " << _id << endl;
            _id = other._id;
            return *this;
        }
        int id() const {
            return _id;
        }
};

ostream& operator<<(ostream& out, const Verbose& v) {
    out << "{id: " << v.id() << "}";
    return out;
}

template<typename T>
void copy_swap(T& a, T& b) {
    T tmp{a}; // useless deep copy Verbose(const Verbose& other): x -> ********
    a = b;
    b = tmp;
}

template<typename T>
void move_swap_with_cast(T& a, T& b) {
    // by casting T& to T&& we say "use move constructor", works if T has move constructor (or move assignment), otherwise copy constructor is used
    T tmp{static_cast<T&&>(a)};
    a = static_cast<T&&>(b);
    b = static_cast<T&&>(tmp);
}

template<typename T>
void move_swap(T& a, T& b) {
    T tmp = move(a); // std::move(x) is exactly the same as static_cast<T&&>(x)
    a = move(b);     // std::move says "here is a rvalue, it will be destoyed after calculation, so don't be shy about appropriating its fields"
    b = move(tmp);   // std::move does not "move" anything, just produces an rvalue reference (&&)
}

template<typename T>
void move_swap_for_2nd_rvalue(T& a, T&& b) { // effectivly overloading move_swap(T&, T&)
    T tmp = move(a);// cannot write 'T&& tmp = move(a)'! It will be reference binging with no constructor or operator= called
    a = move(b);    // need to write std::move(b), becouse without move, b is not &&, it is just & reference.
    b = move(tmp);
}

int main() {
    Verbose a{1};
    cout << "var a is " << a << endl;

    Verbose b{2};
    cout << "var b is " << b << endl;

    cout << "BEGIN: copy swap a and b" << endl;
    copy_swap(a, b);
    cout << "END:   copy swap a and b" << endl;

    cout << "now var a is " << a << endl;
    cout << "now var b is " << b << endl;
    cout << endl;

    cout << "BEGIN: move swap with cast a and b" << endl;
    move_swap_with_cast(a, b); // new object was created, but by different (move) constructor, that will do light copy (if we have it written that way)!
    cout << "END:   move swap with cast a and b" << endl;

    cout << "now var a is " << a << endl;
    cout << "now var b is " << b << endl;
    cout << endl;

    cout << "BEGIN: move swap a and b" << endl;
    move_swap(a, b);
    cout << "END:   move swap a and b" << endl;

    cout << "now var a is " << a << endl;
    cout << "now var b is " << b << endl;
    cout << endl;
    
    // thous "move" swaps can swap only lvalues
    // No matching function for call to 'move_swap': candidate function [with T = Verbose] not viable: expects an l-value for 2nd parameter
    COMPILATION_ERROR(
        move_swap(b, Verbose(3)); // Verbose(3) is an rvalue, types of argument and parameter do not match, need to do overloading
    );

    cout << "BEGIN: move swap overloaded for 2nd rvalue a and b" << endl;
    move_swap_for_2nd_rvalue(a, Verbose(3));
    // after this function 2 destructors are called, 1 for rvalue argument, 2 for tmp inside function scope
    cout << "END:   move swap overloaded for 2nd rbalue a and b" << endl;

    cout << "now var a is " << a << endl;
    cout << "now var b is " << b << endl;
    cout << endl;

    // references are redusing:
    using rr_i = int&&;
    using lr_i = int&;
    using rr_rr_i = rr_i&&; // ‘int && &&’ is an int&&
    using lr_rr_i = rr_i&;  // ‘int && &’ is an int&
    using rr_lr_i = lr_i&&; // ‘int & &&’ is an int&
    using lr_lr_i = lr_i&;  // ‘int & &’ is an int&
    // & always wins
}
