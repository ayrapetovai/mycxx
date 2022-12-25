#include<iostream>
#include<complex>
#include<bitset>
#include"Utils.hpp"

using namespace std;

// A union is a struct in which all members are allocated at the same address so
// that the union occupies only as much space as its largest member.

// TODO std::variant
// TODO implement anonymous union with constructed field from paragraph 8.3.2

class A {};

union FloatAndInt COMPILATION_ERROR(: A /* Unions cannot have base classes */) {
    public:
        int i;
        float f;
    
        COMPILATION_ERROR(
            int& pi; // Union member 'pi' has reference type 'int &'. A union cannot have members of reference type.
        );
    
    FloatAndInt(const int& new_i): i(new_i) {}
    FloatAndInt(const float& new_f): f(new_f) {}
    
    COMPILATION_ERROR(
        virtual void a_virtual_method() = 0; // Unions cannot have virtual functions
    );

    int count_1bits() const {
        int t = i;
        int count = 0;
        while (t) {
            count += t & 0x1;
            t >>= 1;
        }
        return count;
    }
};

union ToBeBased {};

class B COMPILATION_ERROR(: ToBeBased /* Unions cannot be base classes */) {};

int main() {
    {
        // to conversion is made when accessing to different fields of union
        FloatAndInt fai_int(1);
        FloatAndInt fai_float(1.321f);
        cout << "FloatAndInt(int): int is " << fai_int.i << ", as float is " << fai_int.f << endl;
        cout << "FloatAndInt(int) bits as int   " << bitset<sizeof(int)*8>(fai_int.i) << endl;
        cout << "FloatAndInt(int) bits as float " << bitset<sizeof(float)*8>(*reinterpret_cast<unsigned long*>(&fai_int.f)) << endl;
        cout << "FloatAndInt(float): float is " << fai_float.f << ", as int is " << fai_float.i << endl;
        cout << "FloatAndInt(float) bits as int   " << bitset<sizeof(int)*8>(fai_float.i) << endl;
        cout << "FloatAndInt(float) bits as float " << bitset<sizeof(float)*8>(*reinterpret_cast<unsigned long*>(&fai_float.f)) << endl;
        
        // union can have methods
        cout << "bits in FloatAndInt(int) field 'i' is " << fai_int.count_1bits() << endl;
    }
    {
        // the size of a union is the most size of it's fields
        union U {
            short x_short;
            int   y_int;
        };
        U u;
        u.x_short = 1;
        cout << "size of union {short, int} " << EQUALS_STRING(sizeof(U), max(sizeof(short), sizeof(int))) << " max field size" << endl; // ==
    }
    {
        // deletes constructors (etc.) from a union with a member that has a constructor
        union HasNoConstructor {
            string str;
            complex<float> c;
        };

        union HasConstructor {
            int x;
            float y;
        };

        HasConstructor hc1; // tidy: uninitialized record, replace with `hc1{}` - default initialization
        HasConstructor hc2 = hc1; // ok

        COMPILATION_ERROR(
            HasNoConstructor hnc1;        // Call to implicitly-deleted default constructor of 'HasNoConstructor'
            HasNoConstructor hnc2 = hnc1; // Call to implicitly-deleted copy constructor of 'HasNoConstructor'
            // move constructor and destructor are also deleted
        );
        // reason: cannot call several constructor on the same memory for fields of different types
        // reason: cannot decide which constructor to use on copy
        // reason: cannot decide which destructor to call
        // thous constructors may be defined by user
    }
    {
        // anonymous union
        struct A {
            char type_of_union;
            union {
                int i;
                float f;
            };
        };

        A a1{ 'i', 1};
        A a2{ 'f', .f = 1.f}; // does not compile without '.f ='
        cout << "A(" << a1.type_of_union << ") with anon union: i is " << a1.i << ", f is " << a1.f << endl;
        cout << "A(" << a2.type_of_union << ") with anon union: i is " << a2.i << ", f is " << a2.f << endl;
    }
}
