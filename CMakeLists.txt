cmake_minimum_required(VERSION 3.20)

project(RealEngine)

# Enables the full Tracy project
option ( TRACY_ENABLE "" ON )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DRE_DEBUG")

set(XXHASH_BUILD_ENABLE_INLINE_API ON) #optional
set(XXHASH_BUILD_XXHSUM OFF) #optional
set(BUILD_SHARED_LIBS OFF) #optional

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Makes static libraries to be linked later
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/tracy)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/xxHash/cmake_unofficial)
add_subdirectory(vendor/ImGui)

add_library(RealEngine STATIC 
"src/RealEngine/Core/EntryPoint.h" "src/RealEngine/Core/Application.h" "src/RealEngine/Core/Application.cpp" 
"src/RealEngine.h" "src/RealEngine/Core/Core.h" "src/RealEngine/Core/Log.h" "src/RealEngine/Core/Log.cpp" 
"src/RealEngine/Core/Assert.h" "src/RealEngine/Core/Profiler.h" "src/RealEngine/Core/Layer.h" "src/RealEngine/Core/Layer.cpp" 
"src/RealEngine/Core/LayerStack.h" "src/RealEngine/Core/LayerStack.cpp" "src/RealEngine/Core/Window.h" 
"src/RealEngine/Core/Window.cpp" "src/RealEngine/Events/Event.h" "src/RealEngine/Events/WindowEvents.h" 
"src/RealEngine/Events/MouseEvents.h" "src/RealEngine/Events/KeyEvents.h" "src/RealEngine/Core/KeyCodes.h" 
"src/RealEngine/Core/MouseCodes.h" "src/RealEngine/Core/Inputs.h" "src/RealEngine/Core/Inputs.cpp" 
"src/RealEngine/Types/UUID.h" "src/RealEngine/Types/UUID.cpp" "src/RealEngine/Types/StringHash.h" 
"src/RealEngine/Types/StringHash.cpp" "src/RealEngine/Render/RenderCommands.h" "src/RealEngine/ImGui/ImGuiLayer.cpp" 
"src/RealEngine/ImGui/ImGuiLayer.h" "src/RealEngine/Render/Renderer.h" "src/RealEngine/Render/Renderer.cpp" 
"src/RealEngine/Render/Framebuffer.h" "src/RealEngine/Render/Framebuffer.cpp" "src/RealEngine/Render/Texture.h" "src/RealEngine/Render/Texture.cpp" 
"src/RealEngine/Types/PathHash.h" "src/RealEngine/Types/PathHash.cpp"
"vendor/stb/stb_image.h" "src/RealEngine/Render/Buffer.h" "src/RealEngine/Render/Buffer.cpp" "src/RealEngine/Render/Shader.h" "src/RealEngine/Render/Shader.cpp" "src/RealEngine/Render/VertexArray.h" "src/RealEngine/Render/VertexArray.cpp" "src/RealEngine/Resources/GeneralManager.h" "src/RealEngine/Resources/TextureManager.h")

include_directories(RealEngine PRIVATE
  src
  vendor/stb
)

target_precompile_headers(RealEngine PRIVATE "src/repch.h")

# Platform detection
if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")

	add_compile_definitions(RE_PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
	add_compile_definitions(RE_PLATFORM_LINUX)
endif()

if(MSVC)
	# This is to enable the use of __VA_OPT__
	target_compile_options(RealEngine PUBLIC "/Zc:preprocessor")
endif()

# links the spdlog static library to the executable
target_link_libraries(RealEngine 
spdlog Tracy::TracyClient glfw glad glm xxHash::xxhash imgui)
