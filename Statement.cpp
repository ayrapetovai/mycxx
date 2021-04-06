#include<iostream>
#include<vector>
#include"Utils.hpp"

using namespace std;

int main() {
    {
        // TODO switch
    }
    {
        // range-for statement
        vector<int> v{ 1, 2 , 3 };

        // TODO make a class with begin() and end()

        cout << "vector:";
        for (int x: v) { // left to the : must be an expression, for which we can call v.begin() and v.end() or begin(v) and end(v)
            cout << " " << x;
        }
        cout << endl;

        // 1. compiler look for methods v.begin() and v.end() in sequence, fields do not count.
        // 2. compiler look for functions begin(v) and end(v) in the enclosing scope.
    }
// goto
    {
        int x;
        goto past_assignment;
        x = 2;
past_assignment:
        cout << "goto past assiginment of x, x is (" << x << ")" << endl; // 0

    }
    {
        // cannot goto past initialization of variable
        COMPILATION_ERROR(
            goto past_initializer1; // jump bypasses variable initialization
        );
        int x = 2;
past_initializer1:
        cout << "goto past initializer (does not compile) of x is (" << x << ")" << endl;
    }
    {
        // cannot goto past initialization of variable
        COMPILATION_ERROR(
            goto past_initializer2;
        );
        int y = 1;
past_initializer2:
        cout << "goto past initializer, but variable is not used" << endl;
    }
    {
        goto block2_begin;
        {
            // int y = 2; // compilation error: goto past initialization of variable (goto block1_begin)
block1_begin:
            int x = 2;
            cout << "can goto betwin csopes" << endl;
            goto block2_end;
        }
        {
block2_begin:
            goto block1_begin;
block2_end:;
        }
    }
    {
        // nested for loop exit with goto
        int x = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 1; j++) {
                x++;
                goto outer_for_loop_exit;
            }
        }
outer_for_loop_exit:;
               cout << "Exit outer for loop, iterations were made " << x << endl;
    }
}

