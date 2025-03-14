cmake_minimum_required(VERSION 3.10)
project(CS3388_Assignment4)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS} ${GLFW_LIBRARY_DIRS} ${GLM_LIBRARY_DIRS} ${SDL2_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS} ${GLFW_DEFINITIONS} ${GLM_DEFINITIONS} ${SDL2_DEFINITIONS})

add_executable(assignment4 main.cpp Camera.cpp TexturedMesh.cpp LoadBitmap.cpp)

target_link_libraries(assignment4 ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${GLM_LIBRARIES} ${SDL2_LIBRARIES})