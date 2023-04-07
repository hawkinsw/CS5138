cmake_minimum_required(VERSION 3.20)

project(DisassemblyPractice DESCRIPTION "Practice disassembly")
add_executable(FunctionCall call.c)
add_custom_command(TARGET FunctionCall POST_BUILD COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/Objects COMMAND objdump -Mintel -d $<TARGET_FILE:FunctionCall> > ${CMAKE_CURRENT_SOURCE_DIR}/Objects/FunctionCall.obj)
add_custom_command(TARGET FunctionCall POST_BUILD COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/Objects COMMAND hexdump -C $<TARGET_FILE:FunctionCall> > ${CMAKE_CURRENT_SOURCE_DIR}/Objects/FunctionCall.hex)
add_executable(FunctionCall2 call2.c)
add_custom_command(TARGET FunctionCall2 POST_BUILD COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/Objects COMMAND objdump -Mintel -d $<TARGET_FILE:FunctionCall2> > ${CMAKE_CURRENT_SOURCE_DIR}/Objects/FunctionCall2.obj)
add_custom_command(TARGET FunctionCall2 POST_BUILD COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/Objects COMMAND hexdump -C $<TARGET_FILE:FunctionCall2> > ${CMAKE_CURRENT_SOURCE_DIR}/Objects/FunctionCall2.hex)

