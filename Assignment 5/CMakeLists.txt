cmake_minimum_required(VERSION 3.10)
project(MarchingCubes)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})
add_definitions(${GLFW_CFLAGS_OTHER})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

add_executable(marching_cubes
    src/main.cpp
    src/marching_cubes.cpp
    src/rendering.cpp
    src/camera.cpp
    src/shaders.cpp
    src/utils.cpp
)

target_link_libraries(marching_cubes
    OpenGL::GL
    GLEW::GLEW
    ${GLFW_LIBRARIES}
)
