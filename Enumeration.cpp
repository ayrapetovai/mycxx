#include<iostream>
#include"Utils.hpp"

using namespace std;

// plain  enum is a set of named integer values
enum PlainEnumColor {
    red, // named enum's element is a 'enumerator'
    green,
    blue,
};

enum class ClassEnumColor {
    red,
    green,
    blue, // ,
};

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
        // enum class with enumerators of type
        enum class EnumOfShorts: short {
            one, two
        };
        cout << "EnumOfShorts: short's enumerator's size is " << sizeof(EnumOfShorts::one) << " bytes" << endl; // 2
        cout << "EnumOfShorts's type " << typeid(EnumOfShorts::two).name() << endl; // non-integral type
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
}

