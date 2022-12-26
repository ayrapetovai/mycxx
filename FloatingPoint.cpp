#include<math.h>
#include<iostream>
#include<limits>
#include<bitset>
#include <iomanip>

using namespace std;

// bool, char, int, short, long... are called `integral` types,
// float, double... are called 'floating-point` types,
// both are called `arithmetic` types.

// https://en.wikipedia.org/wiki/Double-precision_floating-point_format

// float - single-precision
// double - double-precision
// long double - extended-precision

// exact meaning of single-, double-, extended- is platform dependent.

// by default floating point literal are double
/* format of double:
    bit double_memory_bitmap[64];
    bit exponent_sing = double_memory_bitmap[63];
    bit exponent_value = double_memory_bitmap[52, 63]; // 63 not inclusive
    bit fraction = double_memory_bitmap[0, 52]; // 52 not inclusive
*/

template<typename T>
bitset<sizeof(T)*8> bits(T d) {
    return { *reinterpret_cast<unsigned long long*>(&d) };
}

int main() {
    cout << "size of float is       " << sizeof(float) << " [" << numeric_limits<float>::min() << ", " << numeric_limits<float>::max() << "], epsilon = " << numeric_limits<float>::epsilon() << endl;
    cout << "size of double is      " << sizeof(double) << " [" << numeric_limits<double>::min() << ", " << numeric_limits<double>::max() << "], epsilon = " << numeric_limits<double>::epsilon() << endl;
    cout << "size of long double is " << sizeof(long double) << " [" << numeric_limits<long double>::min() << ", " << numeric_limits< long double>::max() << "], epsilon = " << numeric_limits<long double>::epsilon() << endl;
    // EPSILON is smallest such that 1.0 + EPSILON != 1.0
    {
        cout << "float's inf       " << bits(numeric_limits<float>::infinity()) << endl;
        cout << "double's inf      " << bits(numeric_limits<double>::infinity()) << endl;
        cout << "long double's inf " << bits(numeric_limits<long double>::infinity()) << endl;
        cout << "0   " << bits<double>(0) << endl;
        cout << "1   " << bits<double>(1) << endl;
        cout << "-1  " << bits<double>(-1) << endl;
    }
    {
        double a = 3 / 2;  // using operator (int + int)
        cout << "3 / 2 == " << a << endl; // 1
    }
    {
        double a = 3.0 / 2; // using operator (double + double)
        cout << "3.0 / 2 == " << a << endl; // 1.5
    }
    {
        double a = 3 / 2.0; // using operator (double + double)
        cout << "3 / 2.0 == " << a << endl; // 1.5
    }
    {
        double a = .1;
//        ios_base::fmtflags saved_format_flags(cout.flags());
        cout << "variable is defined as [double a = .1] but real value is " << setprecision(100) << a << setprecision(6) << endl;
//        cout.flags(saved_format_flags);
    }
    {
        // structure of double
        cout << "double(3.14) is " << bits<double>(3.14) << endl;
        cout << "double(1) is " << bits<double>(1) << endl;
        cout << "double(Integer.MAX == " << numeric_limits<int>::max() << ") is " << bits<double>(numeric_limits<int>::max()) << endl;
    }
    {
        // comparing doubles which are greater than 1 brings no problem
        double three_point_seven = 3.7;
        double two_point_one = 2.1;
        
        double a = three_point_seven / two_point_one + 1;
        double b = -1 + (a + 1); // 2.7619 == 3.7 / 2.1 + 1
        cout << "a is " << a << ", b is " << b << endl;
        cout << "a == b is " << boolalpha << (a == b) << noboolalpha << endl; // false
        cout << "a is " << bits<double>(a) << endl; // a is 0100000000000110000110000110000110000110000110000110000110000110
        cout << "b is " << bits<double>(b) << endl; // b is 0100000000000110000110000110000110000110000110000110000110000110
        cout << "a == b by epsilon is " << boolalpha << (fabs(a - b) <= numeric_limits<double>::epsilon()) << noboolalpha << ", |a - b| == " << fabs(a - b) << endl; // true
    }
    {
        // this is how to compare doubles which are less than 1
        double point_seven = 0.7;
        double point_one = 0.1;

        double a = point_one / point_seven + 0.1; // a is way long than double precision
        double b = -0.1 + (a + .1); // if write 0.242857 <- it will be written by compile to be very different
        cout << "a is " << a << ", b is " << b << endl;
        cout << "a == b is " << boolalpha << (a == b) << noboolalpha << endl; // false
        cout << "a is " << bits<double>(a) << endl; // a is 0011111111001111000101011111000101011111000101011111000101100000
        cout << "b is " << bits<double>(b) << endl; // b is 0011111111001111000101011111000101011111000101011111000101011111
        //                                                                                                    ^ from there to right double makes us happy (position depends on numbers and operations)
        // Compare the module of deference to epsilon is useless, if the expected values are greater than 1
        // TODO prove that
        cout << "a == b by epsilon is " << boolalpha << (fabs(a - b) <= numeric_limits<double>::epsilon()) << noboolalpha << ", |a - b| == " << fabs(a - b) << endl; // true
    }
    {
        double zero = 0;
        double one_by_zero = 1 / zero; // one_by_zero == inf, no runtime error, neither compile error
        cout << "one_by_zero is " << one_by_zero << endl;
        cout << "1 + inf is " << (1.0 + numeric_limits<double>::infinity()) << endl;
    }
}
