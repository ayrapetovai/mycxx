#include<iostream>
#include<bitset>
#include<bit>
#include "Utils.hpp"

using namespace std;

#ifdef _WIN32
    #define PACKED( __struct_declaration_block__ ) __pragma( pack(push, 1) ) __struct_declaration_block__ __pragma( pack(pop) );
#else
    #define PACKED( __struct_declaration_block__ ) __struct_declaration_block__ __attribute__((__packed__));
#endif

// packing can make packed struct to became not portable across different machines and OS
// https://stackoverflow.com/a/45129239

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
            short short_field;
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
            }
        )
        cout << "alignof packed_struct is by " << alignof(packed_struct) << " bytes, but size is " << sizeof(packed_struct) << endl;
    }
    {
        // with alignas on struct do nothing?
        struct notpacked_struct {
            char char_field1;
            short short_field;
            char char_field2;
        };

        notpacked_struct ns {1 , 1, 1};
        long ns_address = reinterpret_cast<long>(&ns);
        long ns_char_filed1_address = reinterpret_cast<long>(&ns.char_field1);
        long ns_short_field_address = reinterpret_cast<long>(&ns.short_field);
        long ns_char_field2_address = reinterpret_cast<long>(&ns.char_field2);
        cout << "alignof(ans) is " << alignof(ns) << endl;
        cout << "sizeof(ans) is  " << sizeof(ns) << endl;
        cout << "ans_char_filed1_address offset: " << (ns_char_filed1_address - ns_address) << endl;
        cout << "ans_short_field_address offset: " << (ns_short_field_address - ns_address) << endl;
        cout << "ans_char_filed2_address offset: " << (ns_char_field2_address - ns_address) << endl;

        alignas (long) notpacked_struct ans {1 , 1, 1};
        long ans_address = reinterpret_cast<long>(&ans);
        long ans_char_filed1_address = reinterpret_cast<long>(&ans.char_field1);
        long ans_short_field_address = reinterpret_cast<long>(&ans.short_field);
        long ans_char_field2_address = reinterpret_cast<long>(&ans.char_field2);
        cout << "alignof(ans) is " << alignof(ans) << endl;
        cout << "sizeof(ans) is  " << sizeof(ans) << endl;
        cout << "ans_char_field1_address offset: " << (ans_char_filed1_address - ans_address) << endl;
        cout << "ans_short_field_address offset: " << (ans_short_field_address - ans_address) << endl;
        cout << "ans_char_field2_address offset: " << (ans_char_field2_address - ans_address) << endl;
    }
    {
        cout << "***alignas for fields" << endl;

        struct aligned_struct {
            alignas (int) unsigned char char_field;
            alignas (int) unsigned short short_field;
        } s { 0xFF, 0xFFFF };

        // [0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00]

        long s_address = reinterpret_cast<long>(&s);
        long s_char_field_address = reinterpret_cast<long>(&s.char_field);
        long s_short_field_address = reinterpret_cast<long>(&s.short_field);
        cout << "alignof(s) is " << alignof(s) << endl;
        cout << "sizeof(s) is  " << sizeof(s) << endl; // 8
        cout << "s_char_field_address offset: " << (s_char_field_address - s_address) << endl;
        cout << "s_short_field_address offset: " << (s_short_field_address - s_address) << endl;

        cout << "s_address < s_char_field_address < s_short_field_address: " << YESNO_STRING(s_address < s_char_field_address < s_short_field_address) << endl;

        // TODO find a way not to use `unsigned long*` in `reinterpret_cast`, but peak the type of pointer automatically
        static_assert(sizeof(s) == sizeof(unsigned long));

        auto bits = bitset<sizeof(s) * 8>{*reinterpret_cast<unsigned long*>(&s)};
        if constexpr (endian::native == endian::little) {
            for (size_t i{}; i < bits.size()/2; i++) {
                // Code below does not work in WSL2, errr: ambigous swap function name
                // std::swap(bits[i], bits[bits.size() - i - 1]);
                char t = bits[i];
		bits[i] = bits[bits.size() - i - 1];
		bits[bits.size() - i - 1] = t;
            }
        }
        cout << "bits of `s` are: [" << bits << "], size=" << bits.size() << endl;
    }
}

