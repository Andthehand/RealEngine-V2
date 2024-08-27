cmake_minimum_required(VERSION 3.20)

project(Editor)

add_executable(Editor "src/EditorAPP.cpp" "src/EditorLayer.h" "src/EditorLayer.cpp")

include_directories(Editor PRIVATE
  ${CMAKE_SOURCE_DIR}/RealEngine/src
  ${CMAKE_SOURCE_DIR}/RealEngine/vendor/ImGui
  src
)

target_link_libraries(Editor RealEngine)