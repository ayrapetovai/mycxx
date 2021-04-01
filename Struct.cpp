#include<iostream>
#include<bitset>
#include"Utils.hpp"

using namespace std;

// An array is an aggregate of elements of the same type. In its simplest form, a struct is an aggregate of elements of arbitrary types

// struct declaration, all below structs belong to different types (type name plays the role)
struct Struct_name1 { // C++-style, declare type
    int field1;
    int field2;
};

struct { // C-style, declare variable
    int field1;
    int field2;
} variable_name;

typedef struct { // C-style, declare type
    int field1;
    int field2;
} Struct_name2;

using Struct_name3 = struct { // C++-style, declare type alias
    int field1;
    int field2;
};

struct MemberDeclarationOrder {
    char a;
    int b;
    char c;
};

// struct name is available right after compiler read it, yet we cannot make an object of it
struct Link {
    Link *link; // compiler does not need to know size of Link to be shure about pointer size.
};

COMPILATION_ERROR(
    struct BadLink { // Definition of 'BadLink' is not complete until the closing '}'
        BadLink bad_link; // Field has incomplete type 'BadLink'
    }; // until this line Badlink is  incomplete
);

int main() {
    {
        cout << "struct S {} is            " << typeid(Struct_name1).name() << endl;
        cout << "struct {} s is            " << typeid(variable_name).name() << endl;
        cout << "typedef struct {} S is    " << typeid(Struct_name2).name() << endl;
        cout << "using S = struct {} is    " << typeid(Struct_name3).name() << endl;

        Struct_name1 s1{ 1, 2 };
        Struct_name2 s2{ 3, 4 };
        Struct_name3 s3{ 5, 6 };

        cout << "structures: ";
        cout << "{" << s1.field1 << ", " << s1.field2 << "} ";
        cout << "{" << s2.field1 << ", " << s2.field2 << "} ";
        cout << "{" << s3.field1 << ", " << s3.field2 << "}" << endl; // {1, 2} {3, 4} {5, 6}

        cout << "struct S {} " << EQUALS_STRING(typeid(Struct_name1), typeid(Struct_name2)) << " typedef struct {} S" << endl;
    }
    {
        // structure pointer dereference opeerator ->
        Struct_name1* sp = new Struct_name1{ 13, 42 };
        int x = sp->field1;
        int y = (*sp).field2;
        delete sp;
    }
    {
        Struct_name1 s1{ 1, 2 };
        Struct_name1 s2{ 3, 4 };
        s1 = s2; // assigning works by default
        cout << "s2 := s1; s2 now: {" << s2.field1 << ", " << s2.field2 << "}" << endl; // {3, 4}
        
        // comparing does not work by default
        COMPILATION_ERROR(
            s1 == s2; // Invalid operands to binary expression ('Struct_name1' and 'Struct_name1')
            s1 != s2; // user must define thous operators
        );
    }
    {
        // members of struct located in memory in ther order they was declared
        MemberDeclarationOrder mdo{ 77, 42, 13 };
        cout << "{ a, b, c } " << "&a " << LESS_STRING((void*)&mdo.a, (void*)&mdo.b) << " &b " <<  LESS_STRING((void*)&mdo.b, (void*)&mdo.c) << " &c" << endl;
        cout << "{char, int, char} align is " << alignof(MemberDeclarationOrder) << endl; // 4, due to int
        // structure of the struct: CcccICccc
        // , where 'C' is one byte of type char that is ued,
        // 'c' is one byte of type char what is just gap (cannot use it),
        // 'I' is sizeof(int) bytes that are used

        // gap are filled with 0, but I dont know if it is standardised, automatic variables guarantied to be 0?
        // alignment need to make struct body machine-independent
        int32_t gap1 = *((int32_t*)&mdo.a);
        cout << "{ char(1), gap(3), int(4), char(1), gap(3) }, first gap is " << bitset<sizeof(int32_t)*8>(gap1) << endl;
        int32_t gap2 = *((int32_t*)&mdo.c);
        cout << "{ char(1), gap(3), int(4), char(1), gap(3) }, econd gap is " << bitset<sizeof(int32_t)*8>(gap2) << endl;
        // TODO Does big endian, little endian infuence on gap position?
        cout << ((int64_t)&mdo == (int64_t)&mdo.a) << endl;
        cout << (int64_t)&mdo + alignof(mdo)*1 << " " << (int64_t)&mdo.b << endl;
        cout << (int64_t)&mdo + alignof(mdo)*2 << " " << (int64_t)&mdo.c << endl; 
    }
    {
        MemberDeclarationOrder* mdop = new MemberDeclarationOrder{ 1, 1, 1 };
        int32_t gap1 = *((int32_t*)&mdop->a);
        cout << "{ char(1), gap(3), int(4), char(1), gap(3) }, first gap is " << bitset<sizeof(int32_t)*8>(gap1) << endl;
        int32_t gap2 = *((int32_t*)&mdop->c);
        cout << "{ char(1), gap(3), int(4), char(1), gap(3) }, econd gap is " << bitset<sizeof(int32_t)*8>(gap2) << endl;
        delete mdop;
    }
}

