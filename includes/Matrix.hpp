#ifndef MATRIX_HPP
#define MATRIX_HPP


#include <vector>
#include <iostream>
#include <stdexcept>

class Matrix{
    public:
        Matrix() {return;};
        Matrix(size_t nb_row, size_t nb_col, float init_value);

        std::vector<float> my_matrix;

        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix); 
  

        Matrix operator*(const Matrix& matrix);
        Matrix operator*(const float& value);

        Matrix operator+(const Matrix& matrix);
        Matrix operator-(Matrix const& matrix);
        Matrix operator/(const float& value);
        Matrix hadamard(const Matrix & matrix);
        Matrix map(float (*f)(float));
        Matrix transpose();



        size_t matrix_nb_row();
        size_t matrix_nb_col();
    
        void set_value(std::vector<float> values);
        float mean();
        float max();
        float min();
        float sum();
        size_t get_size();


    private:
        size_t nb_row;
        size_t nb_col;


};


#endif