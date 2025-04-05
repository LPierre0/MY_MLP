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


Matrix Matrix::map(float (*f)(float)){
    Matrix out = Matrix(this->nb_row, this->nb_col, 0.0f);

    for (size_t i = 0; i < this->get_size(); i++){
        out.my_matrix[i] = f(this->my_matrix[i]);
    }
    return out;
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

Matrix Matrix::operator-(Matrix const& matrix){
    if (this->nb_col != matrix.nb_col || this->nb_row != matrix.nb_row){
        throw std::invalid_argument("Matrix must have the good size to be additionate");
    }
    Matrix out = Matrix(this->nb_row, this->nb_col, 0.0f);

    for (size_t i = 0; i < out.nb_row; i++){
        for (size_t j = 0; j < out.nb_col; j++){
            out.my_matrix[i * out.nb_col + j] = this->my_matrix[i * out.nb_col + j] - matrix.my_matrix[i * out.nb_col + j];
        }
    }
    return out;
}


Matrix Matrix::operator/(const float& value){
    Matrix out = Matrix(this->nb_row, this->nb_col, 0.0f);

    if (value == 0.0f) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    for (size_t i = 0; i < out.get_size(); i++){
        out.my_matrix[i] = this->my_matrix[i] / value;
    }
    return out;
}


Matrix Matrix::operator-(const float& value){
    Matrix out = Matrix(this->nb_row, this->nb_col, 0.0f);

    for (size_t i = 0; i < out.get_size(); i++){
        out.my_matrix[i] = this->my_matrix[i] - value;
    }
    return out;
}

Matrix Matrix::operator*(const float& value){
    Matrix out = Matrix(this->nb_row, this->nb_col, 0.0f);

    for (size_t i = 0; i < out.get_size(); i++){
        out.my_matrix[i] = this->my_matrix[i] * value;
    }
    return out;
}

Matrix Matrix::hadamard(const Matrix& matrix){
    if (this->nb_row != matrix.nb_row or this->nb_col != matrix.nb_col){
        throw std::invalid_argument("Matrix must have the same shape for hadamard product");
    }

    Matrix out = Matrix(this->nb_row, this->nb_col, 0.0f);
    for (size_t i = 0; i < this->get_size(); i++){
        out.my_matrix[i] = this->my_matrix[i] * matrix.my_matrix[i];
    }
    return out;
}


void Matrix::set_value(std::vector<float> values){
    if (values.size() != this->nb_col * this->nb_row){
        throw std::invalid_argument("Values don't have the same size as the matrix.");
    }
    this->my_matrix = values;
}



float Matrix::max(){
    float max = -1000000;
    for (float& elem : this->my_matrix){
        if (elem > max){
            max = elem;
        }
    }
    return max;
}


float Matrix::min(){
    float min = 1000000000;
    for (float& elem : this->my_matrix){
        if (elem < min){
            min = elem;
        }
    }
    return min;
}

float Matrix::mean(){
    float mean = 0;
    for (float& elem : this->my_matrix){
        mean += elem;
    }
    return mean / this->my_matrix.size();
}

float Matrix::sum(){
    float sum = 0;
    for (float& elem : this->my_matrix){
        sum += elem;
    }
    return sum;
}

Matrix Matrix::transpose(){
    Matrix out(this->nb_col, this->nb_row, 0.0f);

    for (size_t i = 0; i < out.nb_row; i++){
        for (size_t j = 0; j < out.nb_col; j++){
            out.my_matrix[i * out.nb_col + j] = this->my_matrix[j * out.nb_row + i];
        }
    }
    return out;
}

int Matrix::ind_max(){
    float max = 0.0f;
    int ind_max = 0;
    for (size_t i = 0; i < this->get_size(); i++){
        if (my_matrix[i] > max){
            max = my_matrix[i];
            ind_max = i;
        }
    }
    return ind_max;
}

size_t Matrix::get_size(){
    return this->nb_row * this->nb_col;
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




