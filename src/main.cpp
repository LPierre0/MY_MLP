#include "Network.hpp"
#include "Function.hpp"




int main(){
    Network network = Network(2, 1, 2, 2);

    network.weights[0].set_value({0.6, 0.3, 0.4, 0.2});
    network.weights[1].set_value({0.8, 0.3, 0.5, 0.1});


    std::vector<float> input = {1.0, 2.0};
    Matrix true_values = Matrix(2, 1, 0.0f);
    std::vector<float> true_vector = {0.0f , 1.0f};
    true_values.set_value(true_vector);
    network.forward(input);

    std::cout << network << std::endl;

    network.compute_backpropagation(true_values);
    std::cout << network.nabla_layer[0];
    std::cout << network.nabla_layer[1];
    std::cout << network.nabla_layer[2] << std::endl;

}