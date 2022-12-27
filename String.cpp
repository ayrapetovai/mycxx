#include<iostream>
#include"Utils.hpp"

using namespace std;

// string literal are statically allocated
const char* foo() {
    return "hello"; // OK, statically allocated, will not be destroyed
}

// TODO std::to_chars, std::from_chars

int main() {

    cout << "basic string" << " " << describe_type(typeid(R"()").name()) << endl;
    // raw string literal R"()"
    cout << R"(raw string "hello", русский текст?)" << " " << describe_type(typeid(R"()").name()) << endl;
    cout << R"*(Write as many "()" as you want, the number of * is complimentary)*" << endl;
    // vc++20: cannot call function "std::operator<<(std::basic_ostream<char, _Traits> &, const char8_t *) [с _Traits=std::char_traits<char>]", it is deleted

    // the order of u/U and r/R is significant
    cout << u8"The official vowels in Danish are: a, e, i, o, u, \u00E6, \u00F8, \u00E5 and y." << " " << describe_type(typeid(u8"").name()) <<  endl; // does not output non latin text
    cout << u8R"(UTF-8 string русский текст?)" << " " << describe_type(typeid(u8R"()").name()) <<  endl; // does not output non latin text
    cout << uR"(UTF-16 string русский текст?)" << " " << describe_type(typeid(uR"()").name()) <<  endl;  // does not output non latin text
    cout << UR"(UTF-32 string русский текст?)" << " " << describe_type(typeid(UR"()").name()) <<  endl;  // does not output non latin text
    cout << LR"(wchar_t string русский текст?)" << " " << describe_type(typeid(LR"()").name()) <<  endl; // does not output non latin text

    // std::string litersl is "blah"s there s is an operator
    cout << "size of the std::string literal is " << "a literal of type std::string"s.size() <<  endl;

    cout << R"("string" is an array of chars, type of "string" terminated by '0' )" << EQUALS_STRING(typeid(""), typeid(const char*)) << " const char*" << endl; // TODO why != ?
    cout << R"(type of "string" is )" << describe_type(typeid("").name()) << endl; // array of 1 char (0)

    cout << "size of empty string is " << sizeof("") << " byte" << endl;
    
    {
        const char* h = "Hello!";
        char* m = "Message"; // error, but accepted in pre-C++11-standard code

        // /bin/bash: line 1: 41467 Bus error: 10           ./String
        // SHELL exit code 138
        RUNTIME_ERROR(
            m[1] = 'E'; // error, assignment to const
        );
    }
    {
        // to be able to modify string place it in a non-const array
        char s[] = "Hello!";
        s[1] = 'E';
        cout << "char array's content " << s << endl; // Hello!
    }
    {
        cout << "string literals are statically allocated, it is OK to return them from function " << foo() << endl;
    }
    {
        const char* s1 = "Hello!";
        const char* s2 = "Hello!";
        cout << "address of string literal " << EQUALS_STRING(s1, s2) << " same string literal" << endl; // ==, but implementation dependant
    }
    {
        cout << "beep at the end of the message\a\n" << endl; // works in MacOS :) to launched from cline prints ""
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
        // string literal caching: caching literals referenced by pointer
        const char s1[] = "abc"
            "defg";            // compile time concatenation
        const char s2[] = "abcdefg"; // compiler does not cache this string from s1's initializer
        cout << R"(The "" "" concatenated string in array char[] is )" << (s1 == s2? "": "not ") << "cached for further usage" << endl; // not

        const char s3[] = "abc";
        const char s4[] = "abc"; // compiler does not cache this string
        cout << R"(The not concatenated string in array char[] is )" << (s3 == s4? "": "not ") << "cached for further usage" << endl; // not

        const char* s5 = "ab"
                         "c";   // compile time concatenation
        const char* s6 = "abc"; // compiler caches this string
        cout << R"(The "" "" concatenated string referenced by pointer is )" << (s5 == s6? "": "not ") << "cached for further usage" << endl; // do

        const char* s7 = "abc"; // compiler caches this string
        const char* s8 = "abc"; // compiler caches this string
        cout << R"(The not concatenated string referenced by pointer is )" << (s7 == s8? "": "not ") << "cached for further usage" << endl; // do
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

        // `sizeof` looks at declaration whereas `strlen` function looks for a '\0' in the char[].

        char b[4] = "AB\0";
        cout << R"(`strlen("AA\0")` is )" << strlen(b) << R"(, but `sizeof(char [4]{"AB\0"})` is )" << sizeof(b) << ", because of declaration `char [4]`" << endl;
        // {}-style array initialization
        char c[4] { "ABC" };

        cout << R"(`char c[4] {"ABC"}` printed as ")" << c << "\"" << endl;
    }
}
