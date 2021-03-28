#include<iostream>
#include<complex>
#include"Utils.hpp"

using namespace std;

// initializer_list mus be homogeneous if it's type is to be deduces by auto:
//     std::initializer_list<T> is '{' expression<T> [ ',' expressions<T> ] '}'
//     expression<T> means "expression of type T"
// otherwise it can hold values of diferent types (TODO why? Is it steal initialier_list<T>?)

int main() {
    // TODO variable of wich types can we intialize wiht initializer_list?
    {
        int a[] = { 1, 2, 3 }; // array initializer, homogeneous initializer list
    }
    {
        auto x = {1, 2, 3};
        COMPILATION_ERROR(
            auto x = { 1, 2, "3" }; // cannot deduce type, ther type deducing is neaded homogeneous initializer_list must have same T arguments
        );
    }
    {
        struct TheQuestion {
            int answer;
            string question;
        };
        TheQuestion tw = { 42, "'the mine question of ...'" }; // struct initializer (exists by default)
        cout << "struct initialized, filds: " << tw.question << ", " << tw.answer << endl;
        cout << "struct initialized, filds: " << tw.question << ", " << tw.answer << endl;
    }
    {
        // TODO prove by assembly
        class InitListConstructorExampleOneField {
            int x;
        public:
            InitListConstructorExampleOneField(const initializer_list<int>& il) {
                cout << "InitListConstructorExampleOneField(const initializer_list<int>&) is called";
                x = *il.begin();
            }
            InitListConstructorExampleOneField(const int& initial_x) : x(initial_x) {
                cout << "InitListConstructorExampleOneField(const int&) is called";
            }
        };
        cout << "Declare variable: InitListConstructorExampleOneField ice = { 1 } ";
        InitListConstructorExampleOneField ice = { 1 }; // initializer_list is to be crated, memory occupied
        cout << endl;
    }
    {
        // TODO prove by assembly
        class InitListConstructorExampleTwoFields {
            int x;
            int y;
        public:
            InitListConstructorExampleTwoFields(const initializer_list<int>& il) {
                cout << "InitListConstructorExampleTwoFields(const initializer_list<int>&) is called, list size is " << sizeof(il) << " bytes"; // 16
                auto it = il.begin();
                x = *it++;
                y = *it;
            }
        };
        cout << "Declare variable: InitListConstructorExampleTwoFields ice = { 1 , 2 } ";
        InitListConstructorExampleTwoFields ice = { 1 , 2 }; // non-homogeneous initializer_list is to be crated, memory occupied
        cout << " instance size is " << sizeof(ice) << endl;
    }
    {
        // TODO Stroustrup says (page 162)
        complex<double> z = { 0, 3.14159 }; // "use construtor". But vc++17 does not use construtor directly is creates initialzier_list<double>?
    }
    {
        // we can iterate over homogeneous initializer_list :)
        cout << "initializer_list<int>";
        for (const auto& x : { 1 , 2, 3, 4 }) {
            cout << " " << x;
        }
        cout << " for(:)" << endl;
    }
    {
        class WithGeterogeneousFields {
            int integer;
            double real;
        public:
            COMPILATION_ERROR(
                WithGeterogeneousFields(const initializer_list< ? >& il) // cannot declare or instantiate template of "multiple" type
            )
                WithGeterogeneousFields(const int& i, const double& d) : integer(i), real(d) {}
        };
        WithGeterogeneousFields x = { 1, 1.1 }; // will not compile for constructor(int& i, double& d) - no const, alsow compiles for constructor(int i, double d)
    }
}
