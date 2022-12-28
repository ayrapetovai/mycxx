cmake_minimum_required (VERSION 3.8)

project ("mycxx")

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
include(ExternalProject)

#FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v2.13.1)
#FetchContent_MakeAvailable(Catch2)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
ExternalProject_Add(magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)
include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
#link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

file(GLOB source_files *.cpp)

foreach (source IN LISTS source_files)
  get_filename_component(name "${source}" NAME_WE)
  add_executable (${name}  "${name}.cpp")
endforeach()

#add_executable (FundamentalTypesTest FundamentalTypesTest.cpp)
#target_link_libraries(FundamentalTypesTest PRIVATE Catch2::Catch2)

