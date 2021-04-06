#include<iostream>
#include"Utils.hpp"

using namespace std;

// plain  enum is a set of named integer values
enum PlainEnumColor {
    red, // named enum's element is a 'enumerator'
    green,
    blue,
};

enum class ClassEnumColor;  // declaration
enum class ClassEnumColor { // definition
    red,
    green,
    blue, // ,
};

// TODO Java style enum
int main() {
    {
        // plain enum can be casted to int implicitly, class enum cannot.
        cout << "plain enum color type is " << typeid(PlainEnumColor::blue).name() << endl;
        cout << "class enum color type is " << typeid(ClassEnumColor::red).name() << endl;

        COMPILATION_ERROR(
            ClassEnumColor cc = PlainEnumColor::green; // Cannot initialize a variable of type 'ClassEnumColor' with an rvalue of type 'PlainEnumColor'
        );

        int enumerator = PlainEnumColor::red; // ok
        COMPILATION_ERROR(
            int enumerator = ClassEnumColor::red; // Cannot initialize a variable of type 'int' with an rvalue of type 'ClassEnumColor'
        );

        COMPILATION_ERROR(
            ClassEnumColor ec = 1; // Cannot initialize a variable of type 'ClassEnumColor' with an rvalue of type 'int'
        );
    }
    {
        // enum class with enumerators of type, underlying type can be integral type only
        enum class EnumOfShorts: short { // default : int
            one, two
        };
        cout << "EnumOfShorts: short's enumerator's size is " << sizeof(EnumOfShorts::one) << " bytes" << endl; // 2
        cout << "EnumOfShorts's type " << typeid(EnumOfShorts::two).name() << endl; // non-integral type
        cout << "EnumOfShorts::two is " << (short) EnumOfShorts::two << endl;

        COMPILATION_ERROR(
            enum class EnueratorWithClassValue: A {} ; //Non-integral type 'A' is an invalid underlying type
        );
    }
    {
        // warining on forgotten enumerator in switch
        enum class InSwitch {
            one, two,
        };
        InSwitch is = InSwitch::one;
        switch (is) {
            case InSwitch::one: break;
                                // enumeration value 'two' not handled in switch
        }

    }
    {
        // each enumerator has an integer value
        enum class EnumeratorsWithValue {
            a = 1,
            b = 3,
        };
        int x = static_cast<int>(EnumeratorsWithValue::a); // extract int value
    }
    {
        // enum cannot be defined the other way it was declared
        enum class A: char;
        COMPILATION_ERROR(
            enum class A: int {}; // Enumeration redeclared with different underlying type 'int' (was 'char') 
            enum class A {}; // Enumeration redeclared with different underlying type 'int' (was 'char')
        );
    }
    {
        // A plain enum can be unnamed
        enum {a = 1, b = 2 };
        int x = a;
        int y = b;
    }
    {
        // plain enum can be implicitly converted to bool, enum classes cannot
        enum PlainEnum { pe };
        enum class ClassEnum { ce };
 
        if (PlainEnum::pe) {} // if pe is not 0
        COMPILATION_ERROR(
            if (ClassEnum::ce) {} // Value of type 'ClassEnum' is not contextually convertible to 'bool'
        );
    }
}

