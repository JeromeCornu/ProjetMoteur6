cmake_minimum_required(VERSION 3.23)

project(moteur)



include(glew.cmake)

add_subdirectory(dep/SDL dep/SDL)

set(IMGUI_USE_OGL3 true)

include(imgui.cmake)
add_executable(moteur main.cpp gc_3d_defs.hpp camera.cpp camera.hpp)


set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)


target_include_directories(moteur PRIVATE ${SDL_INCLUDE_DIR})
target_include_directories(moteur PRIVATE ${GLM_INCLUDE_DIR})
target_include_directories(moteur PRIVATE ${IMGUI_INCLUDE_DIR})

target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32 glew imgui)