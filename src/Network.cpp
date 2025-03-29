#include "Network.hpp"


Network::Network(size_t input_size, size_t nb_hidden_layer, size_t nb_neurons, size_t output_size)
:input_size(input_size), nb_hidden_layer(nb_hidden_layer), nb_neurons(nb_neurons), output_size(output_size){
    weights.push_back(Matrix(nb_neurons, input_size, 1.0f));
    biais.push_back(Matrix(nb_neurons, 1, 1.0f));
    input = Matrix(input_size, 1, 0.0f);

    for (size_t i = 0; i < nb_hidden_layer - 1; i++){
        weights.push_back(Matrix(nb_neurons, nb_neurons, 1.0f));
        biais.push_back(Matrix(nb_neurons, 1, 1.0f));
    }

    for (size_t i = 0; i < nb_hidden_layer; i++){
        pre_activation_layer.push_back(Matrix(nb_neurons, 1, 0.0f));
        activated_layer.push_back(Matrix(nb_neurons, 1, 0.0f));
    }


    weights.push_back(Matrix(output_size, nb_neurons, 1.0f));
    biais.push_back(Matrix(output_size, 1, 1.0f)); 
    output = Matrix(output_size, 1, 0.0f);
    softmaxed_output = Matrix(output_size, 1, 0.0f);
}


std::ostream& operator<<(std::ostream& os, const Network& network)
{

    os << "input size : " << network.input_size << " nb hidden layer : " << network.nb_hidden_layer;
    os << " nb neurons : " << network.nb_hidden_layer << " output size : " << network.output_size;
    os << "\n";

    os << "input \n" << network.input << "\n";


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
    os << "Preactivation layer : \n";
    for (auto& matrix : network.pre_activation_layer){
        os << "Layer " << ++i << "\n";
        os << matrix;
        os << "----------------------------\n";
    }

    i = 0;
    os << "activated layer : \n";
    for (auto& matrix : network.activated_layer){
        os << "Layer " << ++i << "\n";
        os << matrix;
        os << "----------------------------\n";
    }

    os << "output : \n" << network.output << "\n";


    os << "softmaxed output : \n" << network.softmaxed_output << "\n"; 
    return os;
}


void Network::forward(std::vector<float> in){
    input.set_value(in);


    pre_activation_layer[0] = weights[0] * input + biais[0];
    activated_layer[0] = pre_activation_layer[0].map(relu);
    for (size_t i = 1; i < pre_activation_layer.size(); i++){
        std::cout << i << std::endl;
        pre_activation_layer[i] =  weights[i] * activated_layer[i - 1] + biais[i];
        activated_layer[i] = pre_activation_layer[i].map(relu);
    }
    output = weights[weights.size() - 1] * activated_layer[activated_layer.size() - 1] + biais[biais.size() - 1];
    softmaxed_output = output / output.sum();
}


void Network::set_weights(std::vector<float> w, size_t indice){
    weights[indice].set_value(w);
}




