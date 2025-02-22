cmake_minimum_required(VERSION 3.20)

project(Editor)

add_executable(Editor "src/EditorAPP.cpp" "src/EditorLayer.h" "src/EditorLayer.cpp" "src/Panels/FileExplorerPanel.cpp" "src/Panels/PropertiesPanel.h" "src/Panels/PropertiesPanel.cpp" "src/Events/PanelEvents.h" "src/Panels/Panel.h")

include_directories(Editor PRIVATE
  ${CMAKE_SOURCE_DIR}/RealEngine/src
  ${CMAKE_SOURCE_DIR}/RealEngine/vendor/ImGui
  src
)

target_link_libraries(Editor RealEngine)

file(COPY assets DESTINATION "${CMAKE_BINARY_DIR}/Editor")
