#include "Matrix.hpp"
#include "Function.hpp"


float square(float x){
    return x * x;
}


int test_map(){
    Matrix m = Matrix(10, 10, 1.0f);
    for (size_t i = 0; i < m.matrix_nb_col() * m.matrix_nb_row(); i++){
        if (i % 2 == 0){
            m.my_matrix[i] = i;
        }else{
            m.my_matrix[i] = float(i)* -1;
        }
    }
    std::cout << m << std::endl;

    m = m.map(relu);

    std::cout << m << std::endl;
    return 0;
}

int main(){
    test_map();
    return 0;
}