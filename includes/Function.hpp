#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "Matrix.hpp"
#include <stdexcept>
#include <random>

float relu(float x);
float relu_derivate(float x);
float my_exp(float x);
Matrix generate_random_matrix(size_t nb_row, size_t nb_col);
Matrix he_weights_init(size_t nb_row, size_t nb_col);


#endif