#include "Function.hpp"


float relu(float x){
    return (x > 0 ? x : 0);
}


Matrix relu_derivate(Matrix z){
    Matrix out = Matrix(z.matrix_nb_row(), z.matrix_nb_col(), 0.0f);
    for (size_t i = 0; i < out.get_size(); i++){
        out.my_matrix[i] = (z.my_matrix[i] > 0 ? 1 : 0);
    }
    return out;
}

float my_exp(float x) {
    if (x > 88.0f) return std::numeric_limits<float>::max(); // exp(88) ≈ 1e38
    if (x < -100.0f) return 0.0f;
    return std::exp(x);
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


float cross_entropy(Matrix softmaxed_output, Matrix true_value){
    float loss = 0.0f;
    size_t N = softmaxed_output.get_size();
    for (size_t i = 0; i < N; i++){
        loss += true_value.my_matrix[i] * log(softmaxed_output.my_matrix[i] + 10e-8);
    }
    return loss * (-1);
}


Matrix cross_entropy_derivative(Matrix softmaxed_output, Matrix true_value){
    return softmaxed_output - true_value;
}