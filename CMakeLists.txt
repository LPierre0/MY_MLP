cmake_minimum_required(VERSION 3.0)

project(NeuralNetwork)

set(SOURCES 
    src/linear_algebra/Matrix.cpp
    src/Network.cpp
)

set(SOURCES_MAIN
    ${SOURCES}
    src/main.cpp
)



add_executable(neural ${SOURCES_MAIN})
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(neural ${OpenCV_LIBS})
target_include_directories(neural PUBLIC includes)



set(CMAKE_BUILD_TYPE Release)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

add_custom_target(clean-project
    COMMAND rm -rf ../src/*.o
)