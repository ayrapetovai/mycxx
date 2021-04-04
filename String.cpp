#include<iostream>
#include"Utils.hpp"

using namespace std;

// string literal are staticly allocated
const char* foo() {
    return "hello"; // OK, statycli allocated, will not be destroyed
}

// TODO std::to_chars, std::from_chars

int main() {

    cout << "basic string" << " " << typeid(R"()").name() << endl;
    // raw string literal R"()"
    cout << R"(raw string "hello", русский текст?)" << " " << typeid(R"()").name() << endl;
    cout << R"*(Write as many "()" as you whatn, the number of * is complimetary)*" << endl;
    // vc++20: cannot call function "std::operator<<(std::basic_ostream<char, _Traits> &, const char8_t *) [с _Traits=std::char_traits<char>]", it is deleted

    // the order of u/U and r/R is significant
    cout << u8R"(UTF-8 string русский текст?)" << " " << typeid(u8R"()").name() <<  endl;
    cout << uR"(UTF-16 string русский текст?)" << " " << typeid(uR"()").name() <<  endl;
    cout << UR"(UTF-32 string русский текст?)" << " " << typeid(UR"()").name() <<  endl;
    cout << LR"(wchar_t string русский текст?)" << " " << typeid(LR"()").name() <<  endl;

    // std::string litersl is "blah"s there s is an operator
    cout << "size of the std::string literal is " << "a literal of type std::string"s.size() <<  endl;

    cout << R"("string" is an array of chars, type of "string" terminating by '0' )" << EQUALS_STRING(typeid(""), typeid(const char*)) << "const char*" << endl; // TODO why != ?
    cout << R"(type of "string" is )" << typeid("").name() << endl; // array of 1 char (0)

    cout << "size of empty string is " << sizeof("") << " byte" << endl;
    
    {
        const char* h = "Hello!";
        char* m = "Message"; // error, but accepted in pre-C++11-standard code

        // /bin/bash: line 1: 41467 Bus error: 10           ./String
        // shell exit code 138
        RUNTIME_ERROR(
            m[1] = 'E'; // error, assignment to const
        );
    }
    {
        // to be able to modify string place it in a non-const array
        char s[] = "Hello!";
        s[1] = 'E';
        cout << "char array's content " << s << endl; // HEllo!
    }
    {
        cout << "string literals are staticly allocated, it is OK to return them from function " << foo() << endl;
    }
    {
        const char* s1 = "Hello!";
        const char* s2 = "Hello!";
        cout << "address of string literal " << EQUALS_STRING(s1, s2) << " same string literal" << endl; // ==, but implementation dependant
    }
    {
        cout << "beep at the end of the message\a\n" << endl; // works in mac os :)
    }
    {
// vc++17: error C2001. Cannot manage with macros.
#ifndef _WIN32
        COMPILATION_ERROR(        
            char s[] = "abc
                dfg"; // break line like this does not work
        );
#endif
    }
    {
        char s1[] = "abc"
            "defg"; // compiletime concatenation
        char s2[] = "abcdefg";    // does copiler cache this string from s1's initializer?
        cout << R"(The "" "" concatinated string is )" << (s1 == s2? "": "not") << " cached for futher usage" << endl; // no
    }
    {
        // raw string literal can contain a new line
        string s{R"(first line
second line)"};
        cout << "RAW STRING: " << s << endl;
    }
    {
        COMPILATION_ERROR(
            char s[2] = "AB"; // Initializer-string for char array is too long
        );
        char a[2] = { 'A', 'B' }; // OK
        
        // '\0' is to be added to the end of a string always, eveing if the string already has one
        COMPILATION_ERROR(
            char b[3] = "AB\0"; // Initializer-string for char array is too long
        );
        char b[4] = "AB\0";
        cout << R"(strlen("AA\0") is )" << strlen(b) << R"(, but sizeof(char [4]{"AB\0"}) is )" << sizeof(b) << ", becouse of char [4]" << endl;
        // {}-style array initialization
        char c[4] { "ABC" };
    }
}
