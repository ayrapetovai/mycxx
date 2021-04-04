#include<iostream>
#include<bitset>
#include"Utils.hpp"

using namespace std;

// Every struct must have unique definition in program

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
    {
        // define struct in some local scope
        struct Point { int x; int y; };
        Point points[3] = { {4,2}, {6,2}, {1, 0} }; // we can do array of structs, and initialize it with {}-initializer

        struct Array { Point elements[3]; };
        Array arr = {{ {4,2}, {6,2}, {1, 0} }}; // {}-initializer
    }
    {
        struct Int { int x; };
        Int i1 = { 1 };
        Int i2 = i1; // ok, TODO is constructor(const T& other) automaticly generated?
        Int i3 = move(i1); // ok, TODO is constructor(const T&& other) automaticaly generated or falback to constructor(const T& other) is made?

        COMPILATION_ERROR(
            int x = i2; // No viable conversion from 'Int' to 'int'
        );
    }
    {
        // A POD ("Plain Old Data") is an object that can be manipulated as "just data"
        // without worrying about complications of class layouts or user-defined semantics for construction, copy, and move.

        // A POD must have trivial default constructor (either user-defined or default).
        // A POD must not have virtual methods (otherwise each object has pointer to vtable, if we have an array of Base type - the vtable
        // pointers of it's elements may be different - different Subtypes, cannot copy byte by byte).
        // A POD must not have any nonstandard copy/move semantics or destructor, pointer fields.

        struct LikelyPOD { int x; double y; };
        struct LikelyPODSubType: LikelyPOD { char z; };
        cout << "Q: Is { int, double } a POD? A: " << YESNO_STRING(is_pod<LikelyPOD>::value) << endl; // yes
        cout << "Q: Is { {int, double}, char} a POD? A: " << YESNO_STRING(is_pod<LikelyPODSubType>::value) << endl; // no
    }
    {
        // structures with bit-fields, sizeof(short) is 2
        struct BitFilds {
            short x: 12; // = 1, bit-member initializer is c++20 extension
            short y: 4;
        };
        // bit-fields are packed
        BitFilds bf{ 1, 1};
        cout << "align of { x:12, y:4 } is " << alignof(bf) << endl; // 2
        cout << "size of { x:12, y:4 }  is " << sizeof(bf) << " bytes" << endl; // 2, packed!
        cout << "{ x:12 = 1, y:4 = 1 } bits are " << bitset<sizeof(BitFilds)*8>(*(int32_t*)(&bf)) << endl; // 0001000000000001
        cout << "Q: Is { x:12, y:4 } a POD? A: " << YESNO_STRING(is_pod<BitFilds>::value) << endl; // yes
    }
    // bit-fields can can belong only to integral types
    {
        // access to bit-fields in asm:
        // clang++ -S -mllvm --x86-asm-syntax=intel file.cpp
        struct BitFields {
            char left:4;
            char right:4;
        };
        BitFields bf;
        bf.left = 1;
        bf.right = 1;
        /*
         mov     cl, byte ptr [rbp - 8]
         and     cl, -16                    # 0b11110000
         or      cl, 1                      # 0b00000001
         mov     byte ptr [rbp - 8], cl
         mov     cl, byte ptr [rbp - 8]
         and     cl, 15                     # 0b00001111
         or      cl, 16                     # 0b00010000
         mov     byte ptr [rbp - 8], cl
         */
    }
    {
        // bit-field's address
        struct BitFields {
            char x:3;
            char y:5;
        };
        BitFields bf{ 1, 1};
        COMPILATION_ERROR(
            &bf.y; // Address of bit-field requested
            &bf.x; // Address of bit-field requested 
        );
        const char& cref = bf.x; // ok, copy field value
        cout << "for { x:3, y:5} const ref to x gives value " << (int)cref << endl; // 1
        cout << "&(const ref to struct {x:3,y:5}.x) " << EQUALS_STRING((int64_t)&cref, (int64_t)&bf) << " &(struct {x:3,y5})" << endl;
        COMPILATION_ERROR(
            char& ncref = bf.y; // Non-const reference cannot bind to bit-field 'y'
        );
    }
}

