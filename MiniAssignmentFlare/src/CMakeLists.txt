cmake_minimum_required(VERSION 3.16)

project(Flare DESCRIPTION "This shows how sneaky code might send a Flare.")

find_package(CURL REQUIRED COMPONENTS HTTPS)
add_executable(flare flare.cpp)
target_include_directories(flare PUBLIC ${CURL_INCLUDE_DIR})
set_property(TARGET flare PROPERTY CXX_VERSION 17)
target_link_libraries(flare CURL::libcurl)
install(TARGETS flare)
