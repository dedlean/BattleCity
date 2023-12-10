cmake_minimum_required(VERSION 3.26.4 FATAL_ERROR)

set(PROJ BattleCity)

project(${PROJ})

add_executable(${PROJ} 

	src/main.cpp
	src/Renderer/ShaderProgram.cpp
	src/Renderer/ShaderProgram.h
	src/Resources/ResourceManager.cpp
	src/Resources/ResourceManager.h
)

	target_compile_features(${PROJ} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJ} glfw)

target_link_libraries(${PROJ} glad)
add_subdirectory(external/glad)

set_target_properties(${PROJ} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJ} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJ}>/res)