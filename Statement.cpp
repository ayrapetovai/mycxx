#include<iostream>
#include<vector>
#include <array>
#include"Utils.hpp"

using namespace std;

// `IterableRange` does not have any `begin()` nor `end()` members, yet it is eligible to looped in "rage-for".
class IterableRange {
public:
    int start;
    int excluding_limit;

    IterableRange(int s, int el): start(s), excluding_limit(el) {}
    class Iterator {
        int next;
    public:
        Iterator(int f): next(f) {}
        int operator*() const {
            return next;
        }
        bool operator!=(const Iterator& other) const {
            return this->next != other.next;
        }
        Iterator& operator++() {
            next++;
            return *this;
        }
    };

};

IterableRange::Iterator begin(const IterableRange& iterable) {
    return IterableRange::Iterator{iterable.start };
}

IterableRange::Iterator end(const IterableRange& iterable) {
    return IterableRange::Iterator{iterable.excluding_limit };
}

int main() {
    {
        // limiting the scope of variable to `if` statement
        if (int x = 3; x != 2) {
            cout << "if (init_definition; condition_expr) {}" << endl;
        }
        COMPILATION_ERROR(
            x; // Use of undeclared identifier 'x'
        )

        // useful with locks
        mutex mtx;
        volatile int some_shared_var = 2;
        if(std::lock_guard _(mtx); some_shared_var == 2) {}
    }
    {
        // declarations in conditions
        auto foo = []() { return 3.14; };
        double r = 2;

        // `pi` lives in `if`'s scope
        if (double pi{foo()}) {     // also: if (double pi = foo()) {
            double s = 2 * pi * r;
            cout << "declaration is condition: s is " << s << endl;
        }

        COMPILATION_ERROR(
            cout << pi << endl; // Use of undeclared identifier 'pi'
        )
    }
    {
        int x = 1;
        COMPILATION_ERROR(
            switch(x) {
                case 0:
                    int y = 2;
                case 1: // Cannot jump from switch statement to this case label jump bypasses variable initialization
                    cout << y;
            }
        )
    }
    {
        // jump table, see `$THIS_REPO/res/jump-table/*.s`

        // for switch variant to be compiled with no optimization, compiler build "jump table":
        //	.data_region jt32
        //.set L0_0_set_3, LBB0_3-LJTI0_0
        //.set L0_0_set_4, LBB0_4-LJTI0_0
        //.set L0_0_set_5, LBB0_5-LJTI0_0
        //.set L0_0_set_6, LBB0_6-LJTI0_0
        //.set L0_0_set_7, LBB0_7-LJTI0_0
        //.set L0_0_set_8, LBB0_8-LJTI0_0
        //.set L0_0_set_9, LBB0_9-LJTI0_0
        //.set L0_0_set_10, LBB0_10-LJTI0_0
        //.set L0_0_set_11, LBB0_11-LJTI0_0
        //.set L0_0_set_12, LBB0_12-LJTI0_0
        //LJTI0_0:
        //	.long	L0_0_set_3
        //	.long	L0_0_set_4
        //	.long	L0_0_set_5
        //	.long	L0_0_set_6
        //	.long	L0_0_set_7
        //	.long	L0_0_set_8
        //	.long	L0_0_set_9
        //	.long	L0_0_set_10
        //	.long	L0_0_set_11
        //	.long	L0_0_set_12
        //	.end_data_region

        // for switch variant to be compiled with optimization -O2, compiler eliminates all code (except `cout << 5`),
        // replaces code with compile-time computed value of `i` to 5
        {
            array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
            int i;
            for (int x: a) {
                switch (x) {
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
            cout << i << endl;
        }

        // for if-else variant to be compiled with no optimization
        // compiler builds more jumps (after each `if`), more than in if-no-else variant.

        // for if-else variant to be compiled with optimization -O2, compiler eliminates all code (except `cout << 5`),
        // replaces code with compile-time computed value of `i` to 5
        {
            std::array<int, 10> a = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            int i;
            for (int x: a) {
                if (x == 0) i = 2;
                else if (x == 1) i = 6;
                else if (x == 2) i = 3;
                else if (x == 3) i = 9;
                else if (x == 4) i = 7;
                else if (x == 5) i = 8;
                else if (x == 6) i = 1;
                else if (x == 7) i = 4;
                else if (x == 8) i = 0;
                else if (x == 9) i = 5;
            }
            std::cout << i << endl;
        }

        // for if-no-else variant to be compiled with no optimization
        // compiler builds a lot of jumps

        // as to be optimized -O2: jumps replaced with `cmove` - "move a to b if `cmp`"
        // this variant is less eligible for optimization
        {
            array<int, 10> a = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            int i;
            for (int x: a) {
                if (x == 0) i = 2;
                if (x == 1) i = 6;
                if (x == 2) i = 3;
                if (x == 3) i = 9;
                if (x == 4) i = 7;
                if (x == 5) i = 8;
                if (x == 6) i = 1;
                if (x == 7) i = 4;
                if (x == 8) i = 0;
                if (x == 9) i = 5;
            }
            std::cout << i << endl;
        }
    }
    {
        // range-for statement
        vector<int> v{ 1, 2 , 3 };

        cout << "iterating vector with vector.begin/end :";
        for (int x: v) { // left to the : must be an expression, for which we can call v.begin() and v.end() or begin(v) and end(v)
            cout << " " << x;
        }
        cout << endl;

        // 1. compiler look for methods v.begin() and v.end() in sequence, fields do not count.
        // 2. compiler look for functions std::begin(v) and std::end(v) in the enclosing scope.

        cout << "iterating vector with std::begin/end :";
        for (auto x = begin(v); x != end(v); x++) {
            cout << " " << *x;
        }
        cout << endl;
    }
    {
        cout << "iterating IterableRange with functions begin/end :";
        IterableRange iterable{ 3, 10 };
        for(int x: iterable) {
            cout << " " << x;
        }
        cout << endl;
        // prints " 3 4 5 6 7 8 9"
    }
// goto
    {
        int x;
        goto past_assignment;
        x = 2;
past_assignment:
        cout << "goto past assignment of x, x is (" << x << ")" << endl; // 0

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
            goto past_initializer2; // Cannot jump from this goto statement to its label
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
    {
        COMPILATION_ERROR(
            do {} while(); // Expected expression in ()
        )

        COMPILATION_ERROR(
            while() {} // Expected expression in ()
        )

        COMPILES(
            for(;;) {} // OK, infinite loop
        )
    }
}

