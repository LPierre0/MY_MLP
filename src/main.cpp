#include "Matrix.hpp"

int main(){
    Matrix my_matrix_1 = Matrix(2000, 2000, 1.0f);
    Matrix my_matrix_2 = Matrix(2000, 2000, 1.0f);

    Matrix my_matrix_3 = my_matrix_1 * my_matrix_2;
}