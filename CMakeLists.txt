cmake_minimum_required(VERSION 3.20)

project(Engine)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DRE_DEBUG")

# Platform detection
if (WIN32)
	add_compile_definitions(RE_PLATFORM_WINDOWS)
endif (WIN32)

if(UNIX AND NOT APPLE)
	add_compile_definitions(RE_PLATFORM_LINUX)
endif()

add_subdirectory(RealEngine)
add_subdirectory(Sandbox)
