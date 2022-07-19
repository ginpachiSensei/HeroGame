cmake_minimum_required(VERSION 3.5)
project(HeroGame VERSION 0.99 LANGUAGES C CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

# BUILD EXTERNAL LIBRARIES
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
ExternalProject_Add(SFML

	# GIT_REPOSITORY https://github.com/ginpachiSensei/SFML.git
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext/SFML
	CMAKE_ARGS
	-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
	-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
ExternalProject_Get_Property(SFML INSTALL_DIR)
set(SFML_LIB ${INSTALL_DIR})

# ADD SOURCE FILES AND HEADERS OF EXECUTABLE
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include ${SFML_LIB}/include)

file(GLOB PROJECT_HEADERS source/*.h)
file(GLOB PROJECT_SOURCE source/*.cpp)
file(GLOB ENGINE_HEADERS source/Engine/*.h)
file(GLOB ENGINE_SOURCE source/Engine/*.cpp)

# LINK EXTERNAL LIBRARIES TO EXECUTABLE
LINK_DIRECTORIES(${SFML_LIB}/lib)

# ADD EXECUTABLE
add_executable(HeroGame ${PROJECT_HEADERS} ${PROJECT_SOURCE} ${ENGINE_HEADERS} ${ENGINE_SOURCE})

if(MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT HeroGame)
	set_target_properties(TestGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Build")
	set_target_properties(TestGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Build")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif(MSVC)

# ADD DEPENDISIES FOR EXECUTABLE
add_dependencies(HeroGame SFML)

TARGET_LINK_LIBRARIES(HeroGame
	optimized sfml-system debug sfml-system-d
	optimized sfml-window debug sfml-window-d
	optimized sfml-graphics debug sfml-graphics-d
	optimized sfml-audio debug sfml-audio-d)

# POST BUILD SCRIPTS
set(POST_LIB_DIR "lib")

if(WIN32)
	set(POST_LIB_DIR "bin")
endif()

ADD_CUSTOM_COMMAND(TARGET HeroGame POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${SFML_LIB}/${POST_LIB_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/res" "${CMAKE_CURRENT_BINARY_DIR}/res")
