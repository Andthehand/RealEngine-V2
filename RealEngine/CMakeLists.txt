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
"src/RealEngine/Core/LayerStack.h" "src/RealEngine/Core/LayerStack.cpp" "src/RealEngine/Core/Window.h" "src/RealEngine/Core/Window.cpp" "src/RealEngine/Events/Event.h" "src/RealEngine/Events/WindowEvents.h" "src/RealEngine/Events/MouseEvents.h" "src/RealEngine/Events/KeyEvents.h" "src/RealEngine/Core/KeyCodes.h" "src/RealEngine/Core/MouseCodes.h" "src/RealEngine/Core/Inputs.h" "src/RealEngine/Core/Inputs.cpp")

include_directories(Sandbox PRIVATE
  src
)

target_precompile_headers(RealEngine PRIVATE "src/repch.h")

if(MSVC)
	# This is to enable the use of __VA_OPT__
	target_compile_options(RealEngine PUBLIC "/Zc:preprocessor")
endif()

# links the spdlog static library to the executable
target_link_libraries(RealEngine 
spdlog Tracy::TracyClient glfw glad glm)