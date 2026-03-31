cmake_minimum_required(VERSION 3.10)

project(hooke LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(hooke
    src/main.cpp
    src/app/app.cpp
    src/core/node.cpp
    src/core/world.cpp
    src/physics/physics.cpp
    src/physics/collision.cpp
    src/physics/solver.cpp
    src/renderer/renderer.cpp
    src/ui/ui.cpp

    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_sdl2.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(hooke PRIVATE
    include
    src
    external/imgui
    external/imgui/backends
)

target_link_libraries(hooke PRIVATE
    SDL2::SDL2
    OpenGL::GL
)