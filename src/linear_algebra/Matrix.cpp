#include "Matrix.hpp"


Matrix::Matrix(size_t nb_row, size_t nb_col, float init_value) : nb_row(nb_row), nb_col(nb_col){
    for (size_t i = 0; i < nb_row * nb_col; i++){
        my_matrix.push_back(init_value);
    }
}

size_t Matrix::matrix_nb_row(){
    return this->nb_row;
}

size_t Matrix::matrix_nb_col(){
    return this->nb_col;
}


Matrix Matrix::operator*(Matrix const& matrix){
    if (this->nb_col != matrix.nb_row){
        throw std::invalid_argument("Matrix must have the good size to be multiplacte");
    }

    Matrix out = Matrix(this->nb_row, matrix.nb_col, 0.0f);

    for (size_t i = 0; i < out.nb_row; i++){
        for (size_t j = 0; j < out.nb_col; j++){
            float sum = 0.0f;

            for (size_t k = 0; k < this->nb_row; k++){
                sum += this->my_matrix[i * this->nb_col + k] * matrix.my_matrix[k * out.nb_col + j];
            }
            out.my_matrix[i * out.nb_col + j] = sum;
        }
    }
    return out;
}




std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{

    for (size_t i = 0; i <  matrix.nb_row ;i++){
        for (size_t j = 0; j < matrix.nb_col; j++){
            os << "[" << matrix.my_matrix[i * matrix.nb_col + j] << "]";
        }
        os << "\n";
    }
    return os;
}