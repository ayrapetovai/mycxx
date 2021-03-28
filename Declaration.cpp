#include<iostream>
#include<complex>
#include"Utils.hpp"

using namespace std;

// identifier - /[_a-zA-Z$]([_0-9a-zA-Z$])*/, no keywords, no @, no $ (but vc++17 does not complain)
// names that starts with /__/ or /_[A-Z]/ are reserved, better not to use them

int x = 2; // global scope x

namespace N {
	class A {
		// class scope
	public:
		static const int x = 4; // x shedows ::x in class members
	};

	// naspace scope
	void foo() {
		// local scope
		{
			// local scope
		}
		if (int x = 1; x == 1) { // statement scope x, shedowing ::x
			// local scope
			::x = 3; // accessing global scope x by namespace qualifier :: with no name - global
		}
		A::x; // x of class A

		WILL_NOT_COMPILE(
			void bar() {} // cannot declare non-global, non-class, non-struct fanction, use labdas
		);

	} // global functions and namespaces need no trailing ;
} // global functions and namespaces need no trailing ;

int y = N::A::x;

// paragraph 6.3, page 155 (166)
int main() {
	// TODO declaration with definition
	// TODO initialization
	// TODO Structure of declaration
	// TODO name -> left -> right rule of declaration reading
	// TODO examples of complex declarations
	// TODO const
	// TODO parensies role in reclaration
	// TODO describe type nameing acronims, i for int, template class naming etc.
	{
		int* name1; // pointer to an int, equivalent to int(*name)
		int(*name2); // pointer to an int, equivalent to int *name
		cout << "int* name is " << typeid(name1).name() << ", int(*name) is " << typeid(name2).name() << endl;
	}
	{
		int* x, y; // x is pointer to int, y is int
		cout << "x is " << typeid(x).name() << ", y is " << typeid(y).name() << endl;
	}
	{
		int a[1], * b; // a is array, b is pointer
		cout << "a is " << typeid(a).name() << ", b is " << typeid(b).name() << endl;
	}
	{
		// if some construction looks like a declaration - it is!
		(int) (x); // it is not variable x of type int
		cout << "me: what are you, x? x: I am '" << typeid(x).name() << "' *troll_face*" << endl;
		// and... it is int...
		// TODO find confusin declaration with can be mentioned as constructor call but it is not
		WILL_NOT_COMPILE(
			int y(); // TODO why not?
		);
	}
	{
		// ATTENTION! In a declaration () - empty pair of parantheses always means "function".
		complex<double> z1(); // function? yeah :-)
		cout << "me: what are you, z1? z1: I am '" << typeid(z1).name() << "' *troll_face*" << endl;
		complex<double> z2{}; // complecx with default values, as complex<double> z2;
		cout << "me: what are you, z2? z2: I am '" << typeid(z2).name() << endl;
	}
	{
		// TODO what is the name of this feature? extraction?
		auto [x, y] = tuple { 13, 42 };
		cout << "[x, u] is [" << x << ", " << y << "]" << endl;

		WILL_NOT_COMPILE(
			auto [x, y] = { 13, 42 }; // TODO why :,( it look normal...
		);
	}
}
