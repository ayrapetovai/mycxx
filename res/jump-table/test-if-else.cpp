#include <array>
#include <iostream>

int main() {
    std::array<int, 10> a = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int i;
    for (int x: a) {
        if (x == 0)
            i = 2;
        else if (x == 1)
            i = 6;
        else if (x == 2)
            i = 3;
        else if (x == 3)
            i = 9;
        else if (x == 4)
            i = 7;
        else if (x == 5)
            i = 8;
        else if (x == 6)
            i = 1;
        else if (x == 7)
            i = 4;
        else if (x == 8)
            i = 0;
        else if (x == 9)
            i = 5; 
    }
    std::cout << i;
}

