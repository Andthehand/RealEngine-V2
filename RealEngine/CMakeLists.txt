cmake_minimum_required(VERSION 3.20)

project(RealEngine)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Makes the spdlog static library to be linked later
add_subdirectory(vendor/spdlog)

add_library(RealEngine STATIC 
"src/RealEngine/Core/EntryPoint.h" "src/RealEngine/Core/Application.h" "src/RealEngine/Core/Application.cpp" 
"src/RealEngine.h"   "src/RealEngine/Core/Core.h" "src/RealEngine/Core/Log.h" "src/RealEngine/Core/Log.cpp")

# links the spdlog static library to the executable
target_link_libraries(RealEngine spdlog)