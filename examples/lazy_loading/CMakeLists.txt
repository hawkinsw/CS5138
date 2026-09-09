cmake_minimum_required(VERSION 3.20)

project(Lazy DESCRIPTION "Explore the effects of lazy loading dynamic libraries")

add_executable(lazy source.c)
target_link_options(lazy PRIVATE "-zlazy")

add_executable(now source.c)
target_link_options(now PRIVATE "-znow")