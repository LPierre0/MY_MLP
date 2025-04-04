#include "Network.hpp"
#include "Function.hpp"




void test_2_2_2_2(){
    Network network = Network(2, 1, 2, 2);
    std::vector<float> input = {1.0f, 2.0f};
    Matrix true_values = Matrix(2, 1, 0.0f);
    std::vector<float> true_vector = {1.0f, 0.0f};
    true_values.set_value(true_vector);
    network.weights[0].set_value({0.1, 0.2, 0.3, 0.4});
    network.weights[1].set_value({0.1, 0.3, 0.2, 0.4});

    network.forward(input);

    std::cout << network << std::endl;
    network.compute_backpropagation(true_values);
    std::cout << network.nabla_layer[0] << std::endl;
    std::cout << network.nabla_layer[1] << std::endl;

    std::cout << network << std::endl;

}



int main(){
    test_2_2_2_2();
}