# mycxx
## Learning C++ with "The C++ Programming Language 4th Edition" by Bjarne Stroustrup.
* Must constantly check the [CppCoreGuidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)
* Read code conventions [CodingStandards](https://llvm.org/docs/CodingStandards.html)

## XCode with cmake
mkdir build-xcode
cd build-xcode
cmake .. -GXcode
open mycxx.xcodeproj/

## CLion with cmake
using CLion to make *cmake* work properly (download libs) set:
Settings -> Build, Execution, Deployment -> CMake -> Generator to "Unix Makefiles"

## TODO
- move project to [build2](https://build2.org)?

-------------------------
Q: I define macro #ifdef _WIN32 and it exists on windows 64bit, why? Visual Studio 2019 16.9 says build is "x64-Debug", I saw a linkage against 32bit libs in ninja-files, on the top of it szeof(void*) is 8! Why it is that?  
A: There is a mycxx\out\build\x64-Debug\CMakeCache.txt file with compiler's argument defined:  
//Flags for Windows Resource Compiler during all build types.  
CMAKE_RC_FLAGS:STRING=-DWIN32  
//Flags used by the linker during the creation of modules during  
// all build types.  
CMAKE_MODULE_LINKER_FLAGS:STRING=/machine:x64  
Same for SHARED, STATIC  

-------------------------
