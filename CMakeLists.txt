# Spécifiez la version minimale requise de CMake
cmake_minimum_required(VERSION 3.0)

# Définition du nom du projet
project(NeuralNetwork)

# Déclaration des fichiers source du projet
set(SOURCES 
    src/main.cpp
    src/neuron.cpp
    src/network.cpp
    src/stb_image.cpp
    src/utils.cpp
    src/display.cpp
    src/Preprocessing/preprocessing.cpp
)

# Ajouter un exécutable basé sur les fichiers source
add_executable(neural ${SOURCES})

# Trouver et inclure OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Liaison de l'exécutable avec les bibliothèques OpenCV
target_link_libraries(neural ${OpenCV_LIBS})

# Spécifier les répertoires d'inclusion
target_include_directories(neural PUBLIC includes)

# Définir le mode de compilation
set(CMAKE_BUILD_TYPE Release)  # Mode de compilation Release pour les optimisations

# Activer l'optimisation interprocédurale
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

# Ajouter des drapeaux de compilation supplémentaires
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

