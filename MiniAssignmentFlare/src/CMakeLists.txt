cmake_minimum_required(VERSION 3.16)

project(Flare DESCRIPTION "This shows how sneaky code might send a Flare.")

find_package(CURL REQUIRED COMPONENTS HTTPS)
add_executable(flare flare.cpp)
set_property(TARGET flare PROPERTY CXX_STANDARD 20)
target_include_directories(flare PUBLIC CURL::libcurl)
target_link_libraries(flare CURL::libcurl)
install(TARGETS flare)
install(CODE "execute_process(COMMAND cp ${CMAKE_INSTALL_PREFIX}/bin/flare ${CMAKE_INSTALL_PREFIX}/bin/flares
    COMMAND strip ${CMAKE_INSTALL_PREFIX}/bin/flares)")