#include <array>
#include <iostream>

int main() {
    std::array<int, 10> a = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int i;
    for (int x: a) {
        if (x == 0)
            i = 2;
        if (x == 1)
            i = 6;
        if (x == 2)
            i = 3;
        if (x == 3)
            i = 9;
        if (x == 4)
            i = 7;
        if (x == 5)
            i = 8;
        if (x == 6)
            i = 1;
        if (x == 7)
            i = 4;
        if (x == 8)
            i = 0;
        if (x == 9)
            i = 5; 
    }
    std::cout << i;
}

