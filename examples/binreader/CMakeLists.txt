cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(binreader DESCRIPTION "How to read binary data from a file in C")

add_executable(binreader binreader.c)
if(WIN32)
				target_compile_options(binreader PUBLIC "-DWIN32")
else()
				target_compile_options(binreader PUBLIC "-DUNIX")
endif()

## From https://stackoverflow.com/a/9995088/8887962
add_custom_command(TARGET binreader POST_BUILD 
				COMMAND "${CMAKE_COMMAND}" -E copy 
				"${CMAKE_CURRENT_SOURCE_DIR}/file.bin"
				"$<TARGET_FILE_DIR:binreader>"
				COMMENT "Copying to output directory")
