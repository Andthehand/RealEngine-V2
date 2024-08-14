cmake_minimum_required(VERSION 3.20)

project(RealEngine)

# Enables the full Tracy project
option ( TRACY_ENABLE "" ON )

# Makes the spdlog static library to be linked later
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/tracy)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glm)

add_library(RealEngine STATIC 
"src/RealEngine/Core/EntryPoint.h" "src/RealEngine/Core/Application.h" "src/RealEngine/Core/Application.cpp" 
"src/RealEngine.h" "src/RealEngine/Core/Core.h" "src/RealEngine/Core/Log.h" "src/RealEngine/Core/Log.cpp" 
"src/RealEngine/Core/Assert.h" "src/RealEngine/Core/Profiler.h" "src/RealEngine/Core/Layer.h" "src/RealEngine/Core/Layer.cpp" 
"src/RealEngine/Core/LayerStack.h" "src/RealEngine/Core/LayerStack.cpp" "src/RealEngine/Platforms/Window.h" "src/RealEngine/Platforms/Window.cpp")

include_directories(Sandbox PRIVATE
  src
)

target_precompile_headers(RealEngine PRIVATE "src/repch.h")

# This is to enable the use of __VA_OPT__
target_compile_options(RealEngine PUBLIC "/Zc:preprocessor")

# links the spdlog static library to the executable
target_link_libraries(RealEngine 
spdlog Tracy::TracyClient glfw glad glm)