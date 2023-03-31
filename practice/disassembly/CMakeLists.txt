cmake_minimum_required(VERSION 3.20)

project(DisassemblyPractice DESCRIPTION "Practice disassembly")
add_executable(FunctionCall call.c)
add_custom_command(TARGET FunctionCall POST_BUILD COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/Objects COMMAND objdump -d $<TARGET_FILE:FunctionCall> > ${CMAKE_CURRENT_SOURCE_DIR}/Objects/FunctionCall.obj)
