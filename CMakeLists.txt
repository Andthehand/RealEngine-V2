cmake_minimum_required(VERSION 3.20)

project(Engine)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DRE_DEBUG")

add_subdirectory(RealEngine)
add_subdirectory(Sandbox)
