cmake_minimum_required(VERSION 3.23)

project(moteur)


set(IMGUI_USE_OGL3 true)


set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
add_subdirectory(dep/SDL dep/glm)

include(glew.cmake)
include(assimp.cmake)
include(imgui.cmake)


add_executable(
	moteur main.cpp
	#Geometry.cpp
	Init.cpp
	Init.hpp
	gc_3d_defs.hpp
	loadShader.cpp
	loadShader.hpp
	CubeTuto.cpp
	CubeTuto.hpp
	Texture.cpp
	Texture.hpp
	Camera.cpp
	Camera.hpp
	FPS.cpp
	FPS.hpp
	Matrix.cpp
	Matrix.hpp
	objLoader.cpp
	objLoader.hpp
	ImGuiTool.hpp
	ImGuiTool.cpp
	PathFinder.hpp
	PathFinder.cpp
)



set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)
set(STB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/stb)
set_property(TARGET moteur PROPERTY CXX_STANDARD 17)


target_include_directories(moteur PRIVATE ${SDL_INCLUDE_DIR})
target_include_directories(moteur PRIVATE ${GLM_INCLUDE_DIR})
target_include_directories(moteur PRIVATE ${STB_INCLUDE_DIR})
target_include_directories(moteur PRIVATE ${IMGUI_INCLUDE_DIR})
target_include_directories(moteur PRIVATE ${ASSIMP_INCLUDE_DIR})

target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32 glew imgui assimp)

add_custom_target(copy_asset COMMAND ${CMAKE_COMMAND}
-E copy_directory ${CMAKE_SOURCE_DIR}/asset $<TARGET_FILE_DIR:moteur>/asset)

add_dependencies(moteur copy_asset)


