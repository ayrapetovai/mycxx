#include<iostream>

using namespace std;

int main() {
	// alignof - minimal bytes per field
	cout << "alignment of char is " << alignof(char) << endl;
	cout << "alignment of int is " << alignof(int) << endl;
	cout << "alignment of double is " << alignof(double) << endl;
	{
		struct notpacked_struct {
			char char_filed;
			int int_field;
		};
		cout << "alignof notpacked_struct is by " << alignof(notpacked_struct) << " bytes, but size is " << sizeof(notpacked_struct) << endl;

#ifdef _WIN32
#pragma pack(push,1)
		struct packed_struct {
			char char_filed;
			int int_field;
		};
#pragma pack(pop)
#else
		struct packed_struct {
			char char_filed;
			int int_field;
		} __attribute__((__packed__));
#endif
		cout << "alignof packed_struct is by " << alignof(packed_struct) << " bytes, but size is " << sizeof(packed_struct) << endl;
	}
}
