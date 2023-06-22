cmake_minimum_required(VERSION 3.20)

project(CallingConvention DESCRIPTION "Example of the calling conventions.")
add_executable(CallingConvention calling-convention.c)
target_compile_options(CallingConvention PUBLIC -g -O0)
add_custom_target(Objdump ALL DEPENDS "${CMAKE_SOURCE_DIR}/CallingConvention.obj")
add_custom_command(OUTPUT "${CMAKE_SOURCE_DIR}/CallingConvention.obj" DEPENDS CallingConvention COMMAND objdump -D -Mintel "$<TARGET_FILE:CallingConvention>" > "${CMAKE_SOURCE_DIR}/CallingConvention.obj")
