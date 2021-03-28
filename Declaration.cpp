#include<iostream>

using namespace std;

// identifier - /[_a-zA-Z$]([_0-9a-zA-Z$])*/, no keywords, no @, no $ (but vc++17 does not complain)
// names that starts with /__/ or /_[A-Z]/ are reserved, better not to use them

// paragraph 6.3, page 155 (166)
int main() {
	// TODO declaration with definition
	// TODO initialization
	// TODO Structure of declaration
	// TODO name -> left -> right rule of declaration reading
	// TODO examples of complex declarations
	// TODO const
	// parensies roll in reclaration
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