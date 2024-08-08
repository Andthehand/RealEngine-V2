cmake_minimum_required(VERSION 3.20)

project(RealEngine)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(vendor/spdlog)

add_executable(RealEngine src/main.cpp)
target_link_libraries(RealEngine spdlog)