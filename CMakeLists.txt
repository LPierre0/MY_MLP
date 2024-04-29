cmake_minimum_required(VERSION 3.0)

project(NeuralNetwork)

set(SOURCES 
    src/neuron.cpp
    src/network.cpp
    src/function.cpp
    src/stb_image.cpp
    src/utils.cpp
    src/display.cpp
)

set(SOURCES_MAIN
    ${SOURCES}
    src/main.cpp
)

set(SOURCES_TEST
    ${SOURCES}
    src/test.cpp
)

set(SOURCES_PREPROCESSING
    src/Preprocessing/preprocessing.cpp
)

add_executable(neural ${SOURCES_MAIN})
add_executable(test ${SOURCES_TEST})
add_executable(preprocessing ${SOURCES_PREPROCESSING})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(neural ${OpenCV_LIBS})
target_include_directories(neural PUBLIC includes)

target_link_libraries(test ${OpenCV_LIBS})
target_include_directories(test PUBLIC includes)

target_link_libraries(preprocessing ${OpenCV_LIBS})
target_include_directories(preprocessing PUBLIC includes)


find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

target_link_libraries(neural sfml-graphics sfml-window)
target_include_directories(neural PUBLIC includes)

target_link_libraries(test sfml-graphics)
target_include_directories(test PUBLIC includes)

target_link_libraries(preprocessing sfml-graphics)
target_include_directories(preprocessing PUBLIC includes)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

add_custom_target(clean-project
    COMMAND rm -rf ../src/*.o
)