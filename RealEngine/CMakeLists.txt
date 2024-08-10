cmake_minimum_required(VERSION 3.20)

project(RealEngine)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enables the full Tracy project
option ( TRACY_ENABLE "" ON )
# only starts profiling when connected to the Tracy Profiler
option ( TRACY_ON_DEMAND "" ON )

# Makes the spdlog static library to be linked later
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/tracy)

add_library(RealEngine STATIC 
"src/RealEngine/Core/EntryPoint.h" "src/RealEngine/Core/Application.h" "src/RealEngine/Core/Application.cpp" 
"src/RealEngine.h" "src/RealEngine/Core/Core.h" "src/RealEngine/Core/Log.h" "src/RealEngine/Core/Log.cpp" "src/RealEngine/Core/Assert.h" "src/RealEngine/Core/Profiler.h")

target_precompile_headers(RealEngine PRIVATE "src/repch.h")

# links the spdlog static library to the executable
target_link_libraries(RealEngine 
spdlog Tracy::TracyClient)