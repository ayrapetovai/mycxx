#include<iostream>
#include<vector>

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
}

