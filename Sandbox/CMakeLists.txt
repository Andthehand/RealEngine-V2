cmake_minimum_required(VERSION 3.20)

project(Sandbox)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Sandbox "src/SandboxAPP.cpp" "src/SandboxLayer.h" "src/SandboxLayer.cpp")

include_directories(Sandbox PRIVATE
  ${CMAKE_SOURCE_DIR}/RealEngine/src
  src
)

target_link_libraries(Sandbox RealEngine)