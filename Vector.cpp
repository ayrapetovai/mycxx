#include<vector>
#include<iostream>

using namespace std;

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v) {
    out << "{";
    size_t last = v.size() - 1;
    for (size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last)
            out << ", ";
    }
    out << "}";
    return out;
}

int main() {
    vector<int> v = { 1, 2, 3 };
    cout << v << endl;
    return 0;
}