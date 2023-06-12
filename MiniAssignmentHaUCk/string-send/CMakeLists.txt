cmake_minimum_required(VERSION 3.20)

project(StringSend DESCRIPTION "Example of passing a string to a function.")
add_executable(StringSend string-send.c)
target_compile_options(StringSend PUBLIC -g -O0)
add_custom_target(Objdump ALL DEPENDS "${CMAKE_SOURCE_DIR}/StringSend.obj")
add_custom_command(OUTPUT "${CMAKE_SOURCE_DIR}/StringSend.obj" DEPENDS StringSend COMMAND objdump -D -Mintel "$<TARGET_FILE:StringSend>" > "${CMAKE_SOURCE_DIR}/StringSend.obj")
