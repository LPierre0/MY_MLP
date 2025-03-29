#include "Network.hpp"


Network::Network(size_t input_size, size_t nb_hidden_layer, size_t nb_neurons, size_t output_size)
:input_size(input_size), nb_hidden_layer(nb_hidden_layer), nb_neurons(nb_neurons), output_size(output_size){
    weights.push_back(Matrix(nb_neurons, input_size, 1.0f));
    biais.push_back(Matrix(nb_neurons, 1, 1.0f));
    results_layer.push_back(Matrix(input_size, 1, 0.0f));

    for (size_t i = 0; i < nb_hidden_layer - 1; i++){
        weights.push_back(Matrix(nb_neurons, nb_neurons, 1.0f));
        biais.push_back(Matrix(nb_neurons, 1, 1.0f));
    }

    for (size_t i = 0; i < nb_hidden_layer; i++){
        results_layer.push_back(Matrix(nb_neurons, 1, 0.0f));
    }


    weights.push_back(Matrix(output_size, nb_neurons, 1.0f));
    biais.push_back(Matrix(output_size, 1, 1.0f)); 
    results_layer.push_back(Matrix(output_size, 1, 0.0f));

}


std::ostream& operator<<(std::ostream& os, const Network& network)
{

    os << "input size : " << network.input_size << " nb hidden layer : " << network.nb_hidden_layer;
    os << " nb neurons : " << network.nb_hidden_layer << " output size : " << network.output_size;
    os << "\n";
    os << "weights : \n";
    int i = 0;
    for (auto& matrix : network.weights){
        os << "Layer " << ++i << "\n";

        os << matrix;
        os << "----------------------------\n";
    }
    os << "biais : \n";
    i = 0;
    for (auto& matrix : network.biais){
        os << "Layer " << ++i << "\n";
        os << matrix;
        os << "----------------------------\n";
    }

    i = 0;
    os << "results layer : \n";
    for (auto& matrix : network.results_layer){
        os << "Layer " << ++i << "\n";
        os << matrix;
        os << "----------------------------\n";
    }


    return os;
}


void Network::forward(std::vector<float> input){
    results_layer[0].set_value(input);

    // For each layer
    for (size_t i = 0; i < results_layer.size() - 1; i++){
        results_layer[i + 1] = weights[i] * results_layer[i] + biais[i];
    }
    
}