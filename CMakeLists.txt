# Project Setting
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(OpenGL-Learning LANGUAGES CXX C)


# Enviroment Setting
set(CMake_C_COMPILER "/opt/homebrew/Cellar/llvm/12.0.0/bin/clang")
set(CMake_CXX_COMPILER "/opt/homebrew/Cellar/llvm/12.0.0/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES "arm64")
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/Cellar")
list(APPEND CMAKE_PREFIX_PATH "/Library")


# Import Project Dependencies

## Import GLFW
set(GLFW_DIRS "/opt/homebrew/Cellar/glfw/3.3.8")
set(GLFW_INC "${GLFW_DIRS}/include" CACHE PATH "GLFW include path")
find_library(LIB_GLFW "libglfw.3.3.dylib" "${GLFW_DIRS}/lib")

## Import GLEW
set(GLEW_DIR "/opt/homebrew/Cellar/glew/2.2.0_1")
set(GLEW_INC "${GLEW_DIR}/include" CACHE PATH "GLEW include path")
set(glew_DIR "${GLEW_DIR}/lib/cmake/glew")
find_package(glew CONFIG)
set(LIB_GLEW "GLEW::GLEW")

## Import GLAD
set(GLAD_DIR "/opt/homebrew/Cellar/glad")
set(GLAD_INC "${GLAD_DIR}/include" CACHE PATH "GLAD include path")
set(glad_source "${GLAD_DIR}/src/glad.c")
add_library(GLAD STATIC ${glad_source})
target_include_directories(GLAD
    PRIVATE ${GLAD_INC}
)
set(LIB_GLAD "GLAD")

## Import GLM
set(glm_DIR "/Library/glm/cmake/glm")
find_package(glm CONFIG)
set(GLM_INC ${GLM_INCLUDE_DIRS} CACHE PATH "GLM include")
set(LIB_GLM "glm::glm")

## Import Eigen (Header-Only)
set(EIGEN_INC "/opt/homebrew/Cellar/eigen/3.4.0_1/include/eigen3" CACHE PATH "EIGEN3 include")


# Add Subdirectory
add_subdirectory("Source")
