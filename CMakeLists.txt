project(moteur)

include(glew.cmake)

add_executable(
	moteur main.cpp
	Geometry.cpp
	gc_3d_defs.hpp
	loadShader.cpp
	loadShader.hpp
	CubeTuto.cpp
	CubeTuto.hpp
)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)
set_property(TARGET moteur PROPERTY CXX_STANDARD 17)


add_subdirectory(dep/SDL dep/glm)
target_include_directories(moteur PRIVATE ${SDL_INCLUDE_DIR})
target_include_directories(moteur PRIVATE ${GLM_INCLUDE_DIR})
target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32 glew)