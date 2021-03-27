#include<iostream>

using namespace std;

int main() {
	cout << "basic string" << " " << typeid(R"()").name() << endl;
	cout << R"(raw string "hello" <username>\ можно писать по-русски?)" << " " << typeid(R"()").name() << endl;
	cout << u8R"(UTF-8 string можно писать по-русски?)" << " " << typeid(u8R"()").name() <<  endl;
	cout << uR"(UTF-16 string можно писать по-русски?)" << " " << typeid(uR"()").name() <<  endl;
	cout << UR"(UTF-32 string можно писать по-русски?)" << " " << typeid(UR"()").name() <<  endl;
	cout << LR"(wchar_t string можно писать по-русски?)" << " " << typeid(LR"()").name() <<  endl;
	
	// std::string litersl is "blah"s there s is an operator
	cout << "size of the std::string literal is " << "a literal of type std::string"s.size() <<  endl;
}