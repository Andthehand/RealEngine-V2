cmake_minimum_required(VERSION 3.20)
project(RealEngine LANGUAGES C CXX)

# ------------------------
# Project options
# ------------------------
option(TRACY_ENABLE "Enable Tracy profiler (vendor/tracy)" ON)
option(BUILD_DOCS "Build Doxygen documentation" OFF)
option(BUILD_TESTS "Build tests" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------
# Force-disable unneeded vendor targets
# ------------------------
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(RYML_INSTALL OFF CACHE BOOL "" FORCE)
set(CORAL_TESTING OFF CACHE BOOL "" FORCE)

# ------------------------
# Vendor libraries (static libs / subprojects)
# ------------------------
add_subdirectory(vendor/quill)
add_subdirectory(vendor/tracy)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/ImGui)
add_subdirectory(vendor/rapidyaml)
add_subdirectory(vendor/entt)
add_subdirectory(vendor/coral/cmake)

if(BUILD_DOCS)
    add_subdirectory(docs)
endif()

# ------------------------
# Source files
# ------------------------
set(SOURCE_FILES
    # Core
    src/RealEngine.h
    src/RealEngine/Core/EntryPoint.h
    src/RealEngine/Core/Application.h
    src/RealEngine/Core/Application.cpp
    src/RealEngine/Core/Core.h
    src/RealEngine/Core/Logger.h
    src/RealEngine/Core/Logger.cpp
    src/RealEngine/Core/Assert.h
    src/RealEngine/Core/Profiler.h
    src/RealEngine/Core/Layer.h
    src/RealEngine/Core/Layer.cpp
    src/RealEngine/Core/LayerStack.h
    src/RealEngine/Core/LayerStack.cpp
    src/RealEngine/Core/Window.h
    src/RealEngine/Core/Window.cpp
    src/RealEngine/Core/KeyCodes.h
    src/RealEngine/Core/MouseCodes.h
    src/RealEngine/Core/Input.h
    src/RealEngine/Core/Input.cpp
    src/RealEngine/Core/Project.h
    src/RealEngine/Core/Project.cpp
    "src/RealEngine/Core/Dialogs.h"

    # Events
    src/RealEngine/Events/Event.h
    src/RealEngine/Events/WindowEvents.h
    src/RealEngine/Events/MouseEvents.h
    src/RealEngine/Events/KeyEvents.h

    # Types / Utilities / Formatter
    src/RealEngine/Types/UUID.h
    src/RealEngine/Types/UUID.cpp
    src/RealEngine/Types/StringHash.h
    src/RealEngine/Types/StringHash.cpp
    src/RealEngine/Utils/FileHelper.h
    src/RealEngine/Utils/FileHelper.cpp
    src/RealEngine/Core/yaml.h
    src/RealEngine/Formatter/GLMFormatter.h
    src/RealEngine/Formatter/YAMLFormatter.h
    src/RealEngine/Formatter/STDFormatter.h
    src/RealEngine/Formatter/RealEngineFormatter.h

    # Render
    src/RealEngine/Render/RenderCommands.h
    src/RealEngine/Render/RenderCommands.cpp
    src/RealEngine/Render/Framebuffer.h
    src/RealEngine/Render/Framebuffer.cpp
    src/RealEngine/Render/Texture.h
    src/RealEngine/Render/Texture.cpp
    src/RealEngine/Render/Buffer.h
    src/RealEngine/Render/Buffer.cpp
    src/RealEngine/Render/Shader.h
    src/RealEngine/Render/Shader.cpp
    src/RealEngine/Render/VertexArray.h
    src/RealEngine/Render/VertexArray.cpp
    src/RealEngine/Render/Camera.h
    src/RealEngine/Render/EditorCamera.h
    src/RealEngine/Render/EditorCamera.cpp
    src/RealEngine/Render/SceneRenderer.h
    src/RealEngine/Render/SceneRenderer.cpp

    # ImGui / Fonts
    src/RealEngine/ImGui/ImGuiLayer.h
    src/RealEngine/ImGui/ImGuiLayer.cpp
    src/RealEngine/ImGui/OpenSansRegular.h
    src/RealEngine/ImGui/OpenSansBold.h

    # Scene
    src/RealEngine/Scene/Scene.h
    src/RealEngine/Scene/Scene.cpp
    src/RealEngine/Scene/Entity.h
    src/RealEngine/Scene/Components.h
    src/RealEngine/Scene/ComponentSerializer.h

    # Formatting / vendor headers
    vendor/stb/stb_image.h
 "src/RealEngine/Types/RingBuffer.h"  "src/RealEngine/Core/ImGuiLogSink.h" "src/RealEngine/Asset/AssetManager.h" "src/RealEngine/Asset/Asset.h" "src/RealEngine/Asset/AssetManager.cpp"  "src/RealEngine/Asset/AssetMetadata.h" "src/RealEngine/Asset/AssetImporter.h" "src/RealEngine/Asset/AssetImporter.cpp" "src/RealEngine/Asset/TextureImporter.h" "src/RealEngine/Asset/TextureImporter.cpp" "src/RealEngine/Scripting/ScriptEngine.h" "src/RealEngine/Scripting/ScriptEngine.cpp" "src/RealEngine/Scripting/ScriptGlue.h" "src/RealEngine/Scripting/ScriptGlue.cpp" "src/RealEngine/Formatter/CoreFormatter.h" "src/RealEngine/Events/ProjectEvents.h")

# Platform-specific files
if(WIN32)
    list(APPEND SOURCE_FILES "src/Platform/Windows/WindowsFileDialogs.cpp" "src/Platform/Windows/WindowsInfoDialog.cpp")
elseif(UNIX AND NOT APPLE)
    list(APPEND SOURCE_FILES "src/Platform/Linux/LinuxFileDialogs.cpp" "src/Platform/Linux/LinuxInfoDialog.cpp")
endif()

# ------------------------
# Library target
# ------------------------
add_library(RealEngine STATIC ${SOURCE_FILES})

# Expose public include directory so consumers of the library can use the headers
target_include_directories(RealEngine PUBLIC # Keep public for RealEngineTests to inherit
    src
    vendor/stb
)

# Precompiled header
target_precompile_headers(RealEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/repch.h")

set(CORAL_DIRECTORY "CORAL_DIRECTORY=\"${Coral_BINARY_DIR}\"")

# Compile definitions for configs
target_compile_definitions(RealEngine
    PUBLIC
        ${CORAL_DIRECTORY}
        $<$<CONFIG:Debug>:RE_DEBUG>
        $<$<CONFIG:RelWithDebInfo>:RE_DEBUG>
)

# ------------------------
# Platform-specific flags & libs
# ------------------------
if(WIN32)
    target_compile_options(RealEngine PUBLIC /W4 /WX)
    target_compile_definitions(RealEngine PUBLIC RE_PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(RealEngine PUBLIC RE_PLATFORM_LINUX)

    # GTK3 support for file dialogs (Linux)
    find_package(PkgConfig REQUIRED) 
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0) 
    target_include_directories(RealEngine PRIVATE ${GTK3_INCLUDE_DIRS}) 

    # Link with X11 for ImGui backend
    find_package(X11 REQUIRED)
    target_include_directories(RealEngine PRIVATE ${X11_INCLUDE_DIR})
    set(PLATFORM_LIBS ${GTK3_LIBRARIES} ${X11_LIBRARIES})
endif()

# MSVC-specific behavior
if(MSVC)
    # Enable __VA_OPT__ support
    target_compile_options(RealEngine PUBLIC "/Zc:preprocessor")
endif()

# ------------------------
# Link libraries
# ------------------------
message(STATUS "Linking platform libs: ${PLATFORM_LIBS}")
target_link_libraries(RealEngine 
    quill::quill
    Tracy::TracyClient
    glfw
    glad
    glm
    imgui
    ryml::ryml
    EnTT::EnTT
    Coral.Native
    $<$<BOOL:${PLATFORM_LIBS}>:${PLATFORM_LIBS}>
)

# ------------------------
# Tests
# ------------------------
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(vendor/googletest)
    add_subdirectory(tests)
endif()