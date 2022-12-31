#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main() {
    {
        //           p:
        //     |--------------|
        //     | __ctrl_block |
        //     |--------------|
        //     |--------------|                |------------|
        //     |     &int     |----address---->|     10     |
        //     |--------------|                |------------|

        int *i_p = new int(10);
        shared_ptr<int> p(i_p);
        cout << "shared_ptr<int> p(new int(10)) -> " << *p << endl;
        cout << "&p=" << reinterpret_cast<void*>(&p) << ", i_p=" << reinterpret_cast<void*>(i_p) << endl;

        // `shared_ptr` frees memory when does out of scope
    }
    {
        //           p:
        //     |--------------|
        //     | __ctrl_block |                |------------|
        //     |     &int     |----address---->|     11     |
        //     |--------------|                |------------|

        shared_ptr<int const> p = make_shared<int>(11);
        cout << "shared_ptr<int const> p = make_shared<int>(10) -> " << *p << endl;
    }
    {
        //           p:
        //     |--------------|
        //     | __ctrl_block |                |------------|
        //     |    &vector   |----address---->|     T[]    |
        //     |--------------|                |------------|

        shared_ptr<vector<int>> p = make_shared<vector<int>>();
        p->push_back(12);
        p->push_back(15);

        cout << "shared_ptr<vector<int>> p = make_shared<vector<int>>() -> ";
        std::copy(p->begin(),p->end(), std::ostream_iterator<int>(std::cout, " "));
        cout << endl;
        cout << "&p=" << reinterpret_cast<void*>(&p) << ", i_p=" << reinterpret_cast<void*>(&((*p)[0])) << endl;
    }
    {
        //           p:
        //     |--------------|
        //     | __ctrl_block |
        //     |    &array    |
        //     |      T[]     |
        //     |--------------|

        shared_ptr<array<int, 10>> p = make_shared<array<int, 10>>();
        p->at(1) = 2;
        p->at(7) = 3;

        cout << "shared_ptr<array<int, 10>> p = make_shared<array<int, 10>>() -> ";
        std::copy(p->begin(),p->end(), std::ostream_iterator<int>(std::cout, " "));
        cout << endl;
        cout << "&p=" << reinterpret_cast<void*>(&p) << ", i_p=" << reinterpret_cast<void*>(&((*p)[0])) << endl;
    }
}