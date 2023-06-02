cmake_minimum_required(VERSION 3.16)

project(Flare DESCRIPTION "This shows how sneaky code might send a Flare.")

find_package(CURL REQUIRED COMPONENTS HTTPS)
add_executable(hauck-mfa hauck-mfa.cpp)
set_property(TARGET hauck-mfa PROPERTY CXX_STANDARD 20)
target_include_directories(hauck-mfa PUBLIC CURL::libcurl)
target_link_libraries(hauck-mfa CURL::libcurl)
install(TARGETS hauck-mfa)
install(CODE "execute_process(COMMAND cp ${CMAKE_INSTALL_PREFIX}/bin/hauck-mfa ${CMAKE_INSTALL_PREFIX}/bin/hauck-mfa-s
    COMMAND strip ${CMAKE_INSTALL_PREFIX}/bin/hauck-mfa-s)")