#include<iostream>
#include<vector>
#include"Utils.hpp"

using namespace std;

using alias_for_char_ptr = const char *;

template<typename T>
class TypeAliasAsMember {
    public:
    using member_alias_for_T = T;
};

// c-style
typedef int* pointer_to_int_cstyle;
using pointer_to_int = int *;

template<typename T> using Vector = vector<T>;

int main() {
    cout << "alias " << EQUALS_STRING(typeid(alias_for_char_ptr), typeid(const char *)) << " original type by typeid" << endl; // ==
    {
        TypeAliasAsMember<int>::member_alias_for_T x = 0; // x is int
        cout << "TypeAliasAsMember<int>::member_alias_for_T x is " << typeid(x).name() << endl;
        COMPILATION_ERROR(
            TypeAliasAsMember<int>::T x = 0; // T does not exist as member of the class
        );
    }
    {
        // type aliases are synonims, they are not differ by compiler
        using Pchar = char*;
        Pchar p1 = nullptr; // p1 is a char*
        char* p2 = p1;      // compiles
    }
    {
        // c-style is equvalent to new style
        cout << "pointer_to_int_cstyle " << EQUALS_STRING(typeid(pointer_to_int_cstyle), typeid(pointer_to_int)) << " pointer_to_int" << endl;
    }
    {
        // using can be used with template
        COMPILATION_ERROR(
                template<typename T> using Vector = vector<T>; // declare template only in global or namespace scope
        );
        Vector<int> v(10); // Vector is an template alias
    }
    {
        using Integer = int;
        COMPILATION_ERROR(
            unsigned Integer x{1}; // Redefinition of 'Integer' as different kind of symbol, signed or unsigned is forbidden for alias
        );
        COMPILATION_ERROR(
            signed Integer sx{-1}; // Redefinition of 'Integer' as different kind of symbol,  signed or unsigned is forbidden for alias
        );
        const Integer x {1}; // const - Ok.
        COMPILATION_ERROR(
            x = 2; // cant, x is const
        );
        cout << "const Integer x is " << typeid(x).name() << endl; // x is int
        const Integer &xr = Integer(1); // const reference initialized with temporaty value - Ok.
    }
}
