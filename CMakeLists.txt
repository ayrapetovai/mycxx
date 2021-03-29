cmake_minimum_required (VERSION 3.8)

project ("mycxx")

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

#FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v2.13.1)
#FetchContent_MakeAvailable(Catch2)

# TODO compile all soures in with some generic aproch
add_executable (HelloWorld HelloWorld.cpp)
add_executable (Vector Vector.cpp)
add_executable (FundamentalTypes FundamentalTypes.cpp)
add_executable (Integer Integer.cpp)
add_executable (FloatingPoint FloatingPoint.cpp)
add_executable (String String.cpp)
add_executable (Alignment Alignment.cpp)
add_executable (Declaration Declaration.cpp)
add_executable (Initialization Initialization.cpp)
add_executable (InitializerList InitializerList.cpp)
add_executable (AutoDecltype AutoDecltype.cpp)
add_executable (Move Move.cpp)
add_executable (ObjectLifeTime ObjectLifeTime.cpp)
#add_executable (FundamentalTypesTest FundamentalTypesTest.cpp)
#target_link_libraries(FundamentalTypesTest PRIVATE Catch2::Catch2)

