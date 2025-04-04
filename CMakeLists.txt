cmake_minimum_required(VERSION 3.0)

project(NeuralNetwork)

set(SOURCES 
    src/math/Matrix.cpp
    src/Network.cpp
    src/math/Function.cpp
    src/loader/ImageLoader.cpp
)

set(SOURCES_MAIN
    ${SOURCES}
    src/main.cpp
)

set(SOURCES_TEST
    ${SOURCES}
    src/test.cpp
)

add_executable(neural ${SOURCES_MAIN})
target_include_directories(neural PUBLIC includes)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

add_custom_target(clean-project
    COMMAND rm -rf ../src/*.o
)