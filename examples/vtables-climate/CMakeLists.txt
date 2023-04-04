cmake_minimum_required(VERSION 3.20)

project(VtablesClimate DESCRIPTION "Disassembling vtables!")
add_executable(VtablesClimate climate.cpp)
set_target_properties(VtablesClimate PROPERTIES CXX_STANDARD 20)
