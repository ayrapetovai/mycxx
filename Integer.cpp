#include<iostream>
#include<limits>
#include<bitset>

using namespace std;

template<typename T>
void print_size_of() {
    cout << "size of " << typeid(T).name() << " is " << sizeof(T) << " [" << numeric_limits<T>::min() << ", " << numeric_limits<T>::max() << "] " << (numeric_limits<T>::is_signed ? "signed" : "unsigned") << endl;
}


int main() {
    print_size_of<uint_least32_t>();  // 4
    short overfloved_short1 = 1000000000; // only warning
    // short overfloved_short2{ 1000000000 }; // compilation error
    cout << "-10U is " << -10U << " of size " << sizeof(-10u) << endl;
    // decimal has no suffix -> int, long int, long long int - the first type it can be represented
    // U -> unsigned int, unsigned long int, unsigend long long int
    // L -> long int, long long int
    // ocatal or hexadecimal -> unsigned * if it does not fit to machine word, otherwise signed (must retain all bit values)
}