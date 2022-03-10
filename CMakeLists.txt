project(moteur)

add_executable(
	moteur main.cpp
	Cube.cpp
	gc_3d_defs.hpp
	Sphere.cpp
	Geometry.cpp
)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)

add_subdirectory(dep/SDL dep/SDL)
target_include_directories(moteur PRIVATE ${SDL_INCLUDE_DIR})
target_include_directories(moteur PRIVATE ${GLM_INCLUDE_DIR})
target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32)