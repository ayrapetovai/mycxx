#include <cxxabi.h> // for demangle's abi::__cxa_demangle
#include <memory>   // for std::unique_ptr
//#include <source_location>

#ifndef _MYCXX_UTILS_HPP
#define _MYCXX_UTILS_HPP

#define UNDEFINED_BEHAVIOR(...) /**/

#define COMPILES(...) /**/

#define COMPILATION_ERROR(...) /**/

#define RUNTIME_ERROR(...) /**/

#define EQUALS_STRING(VALUE1, VALUE2) ((VALUE1 == VALUE2)? "==": "!=")

#define LESS_STRING(VALUE1, VALUE2) ((VALUE1 < VALUE2)? "<": ">=")

#define YESNO_STRING(VALUE) (VALUE? "yes": "no")

std::string describe_type(const char* mangled) {
    int status;
    std::unique_ptr<char[], void (*)(void*)> result(
            abi::__cxa_demangle(mangled, nullptr, nullptr, &status), std::free);
    return result ? std::string(result.get()) : "error occurred";
}

//template <typename T>
//void dynamic_assert(T b, const std::source_location& pLocation) noexcept {
//    if (!static_cast<bool>(b))
//    {
//        throw std::logic_error("assertion failed");
//    }
//}

#endif // _MYCXX_UTILS_HPP
