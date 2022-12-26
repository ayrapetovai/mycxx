#include<iostream>
#include<limits>
#include<bitset>
#include "Utils.hpp"

using namespace std;

template<typename T>
void print_size_of() {
    cout << "size of " << typeid(T).name() << " is " << sizeof(T) << " [" << numeric_limits<T>::min() << ", " << numeric_limits<T>::max()  << "] " << (numeric_limits<T>::is_signed ? "signed" : "unsigned") << endl;
}

template<typename A, typename B>
void print_comparison_result(const A& a, const B& b) {
#pragma warning(suppress: 4805) // TODO vc++17 only?
    cout << typeid(A).name() << "(" << a << ") " << (a == b? "==": "!=") << " " << typeid(B).name() << "(" << b << ")" << endl;
}

void print_paragraph_header(const string& name) {
    static bool first_output = true;
    if (first_output) {
        first_output = false;
    }
    else {
        cout << endl << endl;
    }
    cout << "** " << name << endl;
}

string bool_to_string(bool b) {
    return b ? "true" : "false";
}

// integral_types: bool, char, integer
// floating_point_types: float, double, long double
// arithmetic_types: integral_types, floaing_point_types
// user_defined_types: classes, enums

int main() {

    print_paragraph_header("sizes of arithmetic types");

    print_size_of<bool>();         // 1
    print_size_of<char>();           // 1
    print_size_of<wchar_t>();      // 2
    print_size_of<short>();        // 2
    print_size_of<short int>();    // 2
    print_size_of<int>();          // 4
    print_size_of<long int>();     // 4
    print_size_of<long long int>();// 8
    print_size_of<long>();         // 4
    print_size_of<long long>();    // 8
    print_size_of<double>();       // 8
    print_size_of<long double>();  // 8
    // print_size_of<void>(); // compilation error

    print_paragraph_header("integer to boolean comparison");
    cout << "bool(true) is " << true << endl;    // 1
    cout << "bool(false) is " << false << endl;  // 0
    
    // only zero integer is false. If integer is non zero it is true.
    cout << "int(0)" << bool_to_string(int(0)) << endl;   // false
    cout << "int(1)" << bool_to_string(int(1)) << endl;   // true
    cout << "int(-1)" << bool_to_string(int(-1)) << endl; // true
    
    print_comparison_result(int(1), true);   // == type cast, comparing two integers
    print_comparison_result(int(-1), true);  // != type cast, comparing two integers
    print_comparison_result(int(-1), false); // != type cast, comparing two integers
    print_comparison_result(int(0), true);   // != type cast, comparing two integers
    print_comparison_result(int(0), false);  // == type cast, comparing two integers

    print_comparison_result(int(0), double(0.0)); // ==
    cout << "type of (true + 1) is " << typeid(true + 1).name() << endl; // int

    // using {}-initializer syntax to prevent narrowing
    int i{ true };
    cout << "int i{ true } is " << i << endl; // 1
    int* null_ptr_to_int = nullptr;
    // What will be nullptr to be converted to bool?
    cout << "null_ptr_to_int is " << bool_to_string(null_ptr_to_int) << endl; // false

    print_paragraph_header("signed and unsigned");
    char cx = 0;
    signed char scx = -1;
    unsigned char uscx = 1;
    cout << "char " << (typeid(cx) == typeid(scx)? "==": "!=") << " signed char" << endl;
    cout << "char " << (typeid(cx) == typeid(uscx)? "==": "!=") << " unsigned char" << endl;
    cout << "signed char " << (typeid(scx) == typeid(uscx)? "==": "!=") << " unsigned char" << endl;
    // cannot assign pointers to eachother, but can assign actual values.
    // no pointer conversion between signed and unsigned
    COMPILATION_ERROR(
        char* pcx = &uscx;           // value of type "unsigned char *" cannot be used to initialize entity of type "char *"
    );
    COMPILATION_ERROR(
        signed char* pscx = &uscx;   // value of type "unsigned char *" cannot be used to initialize entity of type "signed char *"
    );
    COMPILATION_ERROR(
        unsigned char* puscx = &scx; // value of type "signed char *" cannot be used to initialize entity of type " unsigned char *"
    );
    char vcx = uscx;            // ok
    signed char vscx = uscx;    // ok, platform dependent, uscx value can be greadet than signde char max
    unsigned char vuscx = scx;  // ok

    print_paragraph_header("chars");
    cout << "On my machine char is " << (numeric_limits<char>::is_signed? "signed": "unsigned") << ", " << sizeof(char) << " bytes, in [" << numeric_limits<char>::min() << ", " << numeric_limits<char>::max() << "]" << endl;
#ifdef _WIN32
    char c = 'Ю';     // compilation error on Mac OS: Character too large for enclosing character literal type [character_too_large]
    wchar_t wc = 'Ю'; // compilation error on Mac OS: wchar_t - size is platform dependent, wide enough to hold big charcodes on that platform
    cout << "8 bit char is '" << c << "', 16 bit char is '" << wc << "'" << endl; // vc++20: compilcation error: cannot call function "std::operator<<(std::basic_ostream<char, _Traits> &, const char8_t *) [с _Traits=std::char_traits<char>]", it is deleted
    cout << "8 bit char is " << (int)c << " as int" << endl;   // -32
    cout << "16 bit char is " << (int)wc << " as int" << endl; // 65502
    cout << "type of ('0' + 1) is " << typeid('0' + 1).name() << endl; // int
#endif
    int ii1 = char(256);  // to make a char of 8 bits, right 8 bits are taken from bit representation of literal (rg conversion to char) as compoile time. Then they are copied to int variable.
    cout << "value of char(256) put in int is " << ii1 << endl; // 0
    int ii2 = char(257);
    cout << "value of char(257) put in int is " << ii2 << endl; // 1

    signed char signed_char = -160; // warning: implicit conversion from 'int' to 'char' changes value from 24930 to 98
    unsigned char unsigned_char = signed_char;
    cout << "-160 in hex is " << hex << (short)-160 << " in bin is " << bitset<16> ((short)-160) << dec << endl;
    cout << "signed_char(-160)           is " << (int) signed_char << " hex " << hex << (int) signed_char << dec << endl;
    cout << "unsigned_char(signed_char)  is " << (int) unsigned_char << " hex " << hex << (int) unsigned_char << dec << endl;

    char archaic_char = 'ab'; // type of 'ab' is int
    cout << "type of 'ab' is " << typeid('ab').name() << ", 'ab' is " << 'ab' << ", bits " << bitset<sizeof('ab')*8>('ab') << ", b code is " << bitset<8>('b') << endl;
    cout << "archaic_char is " << archaic_char << endl;

    print_paragraph_header("void");
    COMPILATION_ERROR(
        void x;
    );
    COMPILATION_ERROR(
        void& r;
    );
    void f(); // funtion that does not return value
    void* pv; // pointer to object of unknowen type
    cout << "size of pointer is " << sizeof(pv) << endl;

    // size_t is an implementation-defined unsigned integer of some bytes to represent size of an object in bytes.
    print_paragraph_header("initialization");
    {
        int x;
        // cout << "default value for int is " << x << endl; // vc++17 error: Run-Time Check Failure #3 - The variable 'x' is being used without being initialized.
        cout << "default value char() is '" << char() << "', as int == " << (int) char() << endl;
        cout << "default value int() is " << int() << endl;
        cout << "default value double() is " << double() << endl;
    }
}
