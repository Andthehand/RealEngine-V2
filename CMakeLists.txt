cmake_minimum_required(VERSION 3.20)

project(RealEngine)

# Enables the full Tracy project
option(TRACY_ENABLE "" ON)
option(BUILD_DOCS "Build Doxygen docs" OFF)
option(BUILD_TESTS "Build tests" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(RYML_INSTALL OFF CACHE BOOL "" FORCE)

# Makes static libraries to be linked later
add_subdirectory(vendor/quill)
add_subdirectory(vendor/tracy)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/ImGui)
add_subdirectory(vendor/rapidyaml)
add_subdirectory(vendor/entt)

if(BUILD_DOCS)
	add_subdirectory(docs)
endif(BUILD_DOCS)

add_library(RealEngine STATIC 
"src/RealEngine/Core/EntryPoint.h" "src/RealEngine/Core/Application.h" "src/RealEngine/Core/Application.cpp" 
"src/RealEngine.h" "src/RealEngine/Core/Core.h" "src/RealEngine/Core/Logger.h" "src/RealEngine/Core/Logger.cpp" 
"src/RealEngine/Core/Assert.h" "src/RealEngine/Core/Profiler.h" "src/RealEngine/Core/Layer.h" "src/RealEngine/Core/Layer.cpp" 
"src/RealEngine/Core/LayerStack.h" "src/RealEngine/Core/LayerStack.cpp" "src/RealEngine/Core/Window.h" 
"src/RealEngine/Core/Window.cpp" "src/RealEngine/Events/Event.h" "src/RealEngine/Events/WindowEvents.h" 
"src/RealEngine/Events/MouseEvents.h" "src/RealEngine/Events/KeyEvents.h" "src/RealEngine/Core/KeyCodes.h" 
"src/RealEngine/Core/MouseCodes.h" "src/RealEngine/Core/Input.h" "src/RealEngine/Core/Input.cpp" 
"src/RealEngine/Types/UUID.h" "src/RealEngine/Types/UUID.cpp" "src/RealEngine/Types/StringHash.h" 
"src/RealEngine/Types/StringHash.cpp" "src/RealEngine/Render/RenderCommands.h" "src/RealEngine/Render/RenderCommands.cpp" "src/RealEngine/ImGui/ImGuiLayer.cpp" 
"src/RealEngine/ImGui/ImGuiLayer.h"   
"src/RealEngine/Render/Framebuffer.h" "src/RealEngine/Render/Framebuffer.cpp" "src/RealEngine/Render/Texture.h" "src/RealEngine/Render/Texture.cpp" 
 
"vendor/stb/stb_image.h" "src/RealEngine/Render/Buffer.h" "src/RealEngine/Render/Buffer.cpp" "src/RealEngine/Render/Shader.h" "src/RealEngine/Render/Shader.cpp" "src/RealEngine/Render/VertexArray.h" "src/RealEngine/Render/VertexArray.cpp" "src/RealEngine/Render/Camera.h" "src/RealEngine/Render/EditorCamera.h" "src/RealEngine/Render/EditorCamera.cpp"   "src/RealEngine/Formatter/GLMFormatter.h" "src/RealEngine/Formatter/YAMLFormatter.h" "src/RealEngine/Core/yaml.h" "src/RealEngine/Formatter/STDFormatter.h" "src/RealEngine/Scene/Scene.h" "src/RealEngine/Scene/Entity.h" "src/RealEngine/Scene/Scene.cpp" "src/RealEngine/Scene/Components.h" "src/RealEngine/Formatter/RealEngineFormatter.h" "src/RealEngine/Scene/ComponentSerializer.h"   "src/RealEngine/Utils/FileHelper.h" "src/RealEngine/Utils/FileHelper.cpp" "src/RealEngine/Render/SceneRenderer.h" "src/RealEngine/Render/SceneRenderer.cpp" "src/RealEngine/Core/Project.h" "src/RealEngine/Core/Project.cpp"  )

include_directories(RealEngine PRIVATE
  src
  vendor/stb
)

target_precompile_headers(RealEngine PRIVATE "src/repch.h")
target_compile_definitions(RealEngine
    PUBLIC
      $<$<CONFIG:Debug>:RE_DEBUG>
      $<$<CONFIG:RelWithDebInfo>:RE_DEBUG>
)

# Platform detection
if (WIN32)
	target_compile_options(RealEngine PUBLIC /W4 /WX)

	target_compile_definitions(RealEngine PUBLIC RE_PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
	target_compile_definitions(RealEngine PUBLIC RE_PLATFORM_LINUX)
endif()

if(MSVC)
	# This is to enable the use of __VA_OPT__
	target_compile_options(RealEngine PUBLIC "/Zc:preprocessor")
endif()

# links the spdlog static library to the executable
target_link_libraries(RealEngine 
quill::quill Tracy::TracyClient glfw glad glm imgui ryml::ryml EnTT::EnTT)

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(vendor/googletest)
	add_subdirectory(tests)
endif(BUILD_TESTS)
