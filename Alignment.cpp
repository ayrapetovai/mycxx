#include<iostream>

using namespace std;

int main() {
	cout << "alignment of char is " << alignof(char) << endl;
	cout << "alignment of int is " << alignof(int) << endl;
	cout << "alignment of double is " << alignof(double) << endl;
	{
		struct test_struct {
			char char_filed;
			int int_field;
		};
		cout << alignof(test_struct) << endl;
		//cout << alignof(test_struct::int_field) << endl;
	}
}
