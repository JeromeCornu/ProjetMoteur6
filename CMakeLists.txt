project(moteur)

include(glew.cmake)

add_executable(
	moteur
	main.cpp
	gc_3d_defs.hpp
	Controls.cpp
	Controls.hpp
	SimpleFragmentShader.fragmentshader
	SimpleVertexShader.vertexshader
	geometry.cpp
)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)

add_subdirectory(dep/SDL dep/glm)
target_include_directories(moteur PRIVATE ${SDL_INCLUDE_DIR})
target_include_directories(moteur PRIVATE ${GLM_INCLUDE_DIR})
target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32 glew)