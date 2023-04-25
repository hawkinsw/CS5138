cmake_minimum_required(VERSION 3.20)

project(VtablesSquirrels DESCRIPTION "Disassembling vtables practice!")

add_executable(VtablesSquirrels squirrels.cpp)
set_target_properties(VtablesSquirrels PROPERTIES CXX_STANDARD 20)
#target_compile_options(VtablesSquirrels PUBLIC "-frtti")

# For disassembly.
add_custom_target(DisassemblyTargetAll ALL DEPENDS VtablesSquirrels.obj VtablesSquirrels.sections VtablesSquirrels.hex)
add_custom_command(OUTPUT "${CMAKE_SOURCE_DIR}/VtablesSquirrels.obj" COMMAND objdump -d -Mintel "$<TARGET_FILE:VtablesSquirrels>" > "${CMAKE_SOURCE_DIR}/VtablesSquirrels.obj" DEPENDS "$<TARGET_FILE:VtablesSquirrels>")
add_custom_command(OUTPUT "${CMAKE_SOURCE_DIR}/VtablesSquirrels.hex" COMMAND hexdump -C "$<TARGET_FILE:VtablesSquirrels>" > "${CMAKE_SOURCE_DIR}/VtablesSquirrels.hex" DEPENDS "$<TARGET_FILE:VtablesSquirrels>")
add_custom_command(OUTPUT "${CMAKE_SOURCE_DIR}/VtablesSquirrels.sections" COMMAND readelf -S "$<TARGET_FILE:VtablesSquirrels>" > "${CMAKE_SOURCE_DIR}/VtablesSquirrels.sections" DEPENDS "$<TARGET_FILE:VtablesSquirrels>")
