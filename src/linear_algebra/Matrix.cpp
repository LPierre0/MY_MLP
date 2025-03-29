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

            for (size_t k = 0; k < this->nb_col; k++){
                sum += this->my_matrix[i * this->nb_col + k] * matrix.my_matrix[k * out.nb_col + j];
            }
            out.my_matrix[i * out.nb_col + j] = sum;
        }
    }
    return out;
}


Matrix Matrix::operator+(Matrix const& matrix){
    if (this->nb_col != matrix.nb_col || this->nb_row != matrix.nb_row){
        throw std::invalid_argument("Matrix must have the good size to be additionate");
    }

    Matrix out = Matrix(this->nb_row, this->nb_col, 0.0f);

    for (size_t i = 0; i < out.nb_row; i++){
        for (size_t j = 0; j < out.nb_col; j++){
            out.my_matrix[i * out.nb_col + j] = this->my_matrix[i * out.nb_col + j] + matrix.my_matrix[i * out.nb_col + j];
        }
    }
    return out;
}



void Matrix::set_value(std::vector<float> values){
    if (values.size() != this->nb_col * this->nb_row){
        throw std::invalid_argument("Values don't have the same size as the matrix.");
    }
    this->my_matrix = values;
}



std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{

    os << "nb row : " << matrix.nb_row << " nb col : " << matrix.nb_col << "\n"; 

    for (size_t i = 0; i <  matrix.nb_row ;i++){
        for (size_t j = 0; j < matrix.nb_col; j++){
            os << "[" << matrix.my_matrix[i * matrix.nb_col + j] << "]";
        }
        os << "\n";
    }
    return os;
}

