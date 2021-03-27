#include<iostream>

using namespace std;

int main() {
        cout << "basic string" << " " << typeid(R"()").name() << endl;
        cout << R"(raw string "hello", русский текст?)" << " " << typeid(R"()").name() << endl;
        // vc++20: cannot call function "std::operator<<(std::basic_ostream<char, _Traits> &, const char8_t *) [с _Traits=std::char_traits<char>]", it is deleted
        cout << u8R"(UTF-8 string русский текст?)" << " " << typeid(u8R"()").name() <<  endl;
        cout << uR"(UTF-16 string русский текст?)" << " " << typeid(uR"()").name() <<  endl;
        cout << UR"(UTF-32 string русский текст?)" << " " << typeid(UR"()").name() <<  endl;
        cout << LR"(wchar_t string русский текст?)" << " " << typeid(LR"()").name() <<  endl;

        // std::string litersl is "blah"s there s is an operator
        cout << "size of the std::string literal is " << "a literal of type std::string"s.size() <<  endl;
}
