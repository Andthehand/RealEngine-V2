cmake_minimum_required(VERSION 3.20)

project(Editor)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Editor "src/EditorAPP.cpp" "src/EditorLayer.h" "src/EditorLayer.cpp")

include_directories(Editor PRIVATE
  ${CMAKE_SOURCE_DIR}/RealEngine/src
  src
)

target_link_libraries(Editor RealEngine)