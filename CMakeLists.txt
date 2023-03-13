cmake_minimum_required(VERSION 3.24)
project(implementing_stl)

set(CMAKE_CXX_STANDARD 17)

add_executable(implementing_stl main.cpp traits/qualifiers_traits.h traits/non_sfinae_check_traits.h traits/generic_constructs.h traits/sfinae_traits.h tests/test_objects.h utility/utility.h)
