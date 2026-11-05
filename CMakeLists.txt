
cmake_minimum_required(VERSION 4.4)

project(MarsCos LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenGL and GLFW
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui)

# GLAD
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad)

add_executable(MarsCos
        main.cpp

        # GLAD source
        ${GLAD_DIR}/src/glad.c

        # ImGui source
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp

        # ImGui backends
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(MarsCos PRIVATE
        ${GLAD_DIR}/include
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)

target_link_libraries(MarsCos PRIVATE
        glfw
        OpenGL::GL
)
