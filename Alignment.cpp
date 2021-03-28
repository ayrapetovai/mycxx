#include<iostream>

using namespace std;

#ifdef _WIN32
#define PACKED( __struct_declaration_block__ ) __pragma( pack(push, 1) ) __stuact_declaration_block__ __pragma( pack(pop) );
#else
#define PACKED( __struct_declaration_block__ ) __struct_declaration_block__ __attribute__((__packed__));
#endif

// packing can make packed struct to became not portable across different machines and OS

int main() {
	// alignof - minimal bytes per field
	// if struct is not packed then alignment equals to the most big field size
	cout << "alignment of char is " << alignof(char) << endl;
	cout << "alignment of int is " << alignof(int) << endl;
	cout << "alignment of double is " << alignof(double) << endl;
	{
		struct notpacked_struct {
			char char_filed;
			int int_field;
		};
		cout << "alignof notpacked_struct(char,int) is by " << alignof(notpacked_struct) <<
			" bytes, but size is " << sizeof(notpacked_struct) << endl;
	}
	{
		struct notpacked_struct {
			int int_field;
                        char char_filed;
                };
                cout << "alignof notpacked_struct(int, char) is by " << alignof(notpacked_struct) <<
                        " bytes, but size is " << sizeof(notpacked_struct) << endl; 
	}
	{
		struct notpacked_struct {
			double double_field;
			short int_field;
                        char char_filed;
                };
                cout << "alignof notpacked_struct(double, short, char) is by " << alignof(notpacked_struct) <<
                        " bytes, but size is " << sizeof(notpacked_struct) << endl;
	}
	{
		PACKED(
		struct packed_struct {
			char char_filed;
			int int_field;
		})
		cout << "alignof packed_struct is by " << alignof(packed_struct) << " bytes, but size is " << sizeof(packed_struct) << endl;
	}
}

