#include "Function.hpp"


float relu(float x){
    return (x > 0 ? x : 0);
}


float relu_derivate(float x){
    return (x > 0 ? 1 : 0);
}

float my_exp(float x){
    float ret = (float)exp(1.0/0.8 * x);
    return ret;
}


Matrix generate_random_matrix(size_t nb_row, size_t nb_col){

    Matrix random_matrix(nb_row, nb_col, 0.0f);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f); 

    for (size_t i = 0; i < random_matrix.get_size(); i++) {
        random_matrix.my_matrix[i] = dist(gen);
    }

    return random_matrix;
}


Matrix he_weights_init(size_t nb_row, size_t nb_col){
    return generate_random_matrix(nb_row, nb_col) * sqrt(2.0 / nb_col);
}