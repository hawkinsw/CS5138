cmake_minimum_required(VERSION 3.16)

project(MysteryStrings DESCRIPTION "Strings (wide)")

#add_executable(mysteryw mysteryw.cpp)
add_executable(mystery mystery.cpp)
set_property(TARGET mystery PROPERTY CXX_STANDARD 20)
add_executable(mysteryw mystery.cpp)
target_compile_definitions(mysteryw PUBLIC W=true)