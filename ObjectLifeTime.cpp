#include<memory>
#include<iostream>

using namespace std;

// Classify object based on thier lifetime
// Automatic: object gets dstoryed when its declarate goes out of scope.
// Static: staticly or global declared objects are initialized only once (threadsafely) and get destroyed when program terminates.
// Free Store: 'new' and 'delete' operator are to control lifetime manualy.
// Temporary: automatic objects are intermediate result of expression calculation, each live while whole expression livs.
// Thread-local: objects that are declared 'thrad_local' keyword, can be static or automatic.

// TODO make examples

struct Verbose {
    Verbose() {
        cout << "Verbose()" << endl;
    }
    ~Verbose() {
        cout << "~Verbose()" << endl;
    }
};


int main() {
    {
        cout << "Reference field is not destructed" << endl;
        struct A {
            Verbose& ref_to_verbose;
            A(Verbose& v) : ref_to_verbose(v) {}
        };
        {
            A a{ *(new Verbose()) };
        }
    }
    {
        cout << "Non-reference non-pointer field dectructed" << endl;
        struct B {
            Verbose verbose;
            B(Verbose& v) : verbose(v) {}
        };
        {
            B b{ *(new Verbose()) }; // destructor is called
        }
    }
    {
        cout << "Pointer field's value is not destructed" << endl;
        struct C {
            Verbose* ptr_to_verbose;
            C(Verbose& v) : ptr_to_verbose(&v) {}
        };
        {
            C c{ *(new Verbose()) };
        }
    }
    {
        cout << "Unique pointer field's value is destroyed" << endl;
        struct D {
            unique_ptr<Verbose> uptr_to_verbose;
            D(Verbose &v) : uptr_to_verbose(&v) {}
        };
        {
            D d{ *(new Verbose()) };
        }
    }
}
