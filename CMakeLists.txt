cmake_minimum_required (VERSION 3.8)

project ("mycxx")

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

#FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v2.13.1)
#FetchContent_MakeAvailable(Catch2)

file(GLOB source_files *.cpp)

foreach (source IN LISTS source_files)
  get_filename_component(name "${source}" NAME_WE)
  add_executable (${name}  "${name}.cpp")
endforeach()

#add_executable (FundamentalTypesTest FundamentalTypesTest.cpp)
#target_link_libraries(FundamentalTypesTest PRIVATE Catch2::Catch2)

