#include <array>
#include <iostream>

using namespace std;

int main() {
        // jump table
        array<int, 10> a = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int i;
        for (int x: a) {
            switch(x) {
                case 0: i = 2; break;
                case 1: i = 6; break;
                case 2: i = 3; break;
                case 3: i = 9; break;
                case 4: i = 7; break;
                case 5: i = 8; break;
                case 6: i = 1; break;
                case 7: i = 4; break;
                case 8: i = 0; break;
                case 9: i = 5; break;
            }
        }
        cout << i;
}
