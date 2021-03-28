#include<iostream>

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
	} // functions and namespaces need no trailing ;
} // functions and namespaces need no trailing ;

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

}
