#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "Matrix.hpp"
#include <stdexcept>
#include <random>

float relu(float x);
Matrix relu_derivate(Matrix z);
float my_exp(float x);
Matrix generate_random_matrix(size_t nb_row, size_t nb_col);
Matrix he_weights_init(size_t nb_row, size_t nb_col);
float cross_entropy(Matrix softmaxed_output, Matrix true_value);
Matrix cross_entropy_derivative(Matrix softmaxed_output, Matrix true_value);

#endif