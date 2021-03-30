#include<iostream>

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

// "object havs an identity" means: the object resides at a specific address in memory, and it can be accessed if you know its address and its type.

// In a type name notation X& means "reference to X", it is "lvalue reference"

// TODO make examples

int main() {
}
