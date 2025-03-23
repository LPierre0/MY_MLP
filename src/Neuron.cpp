#include "../includes/Neuron.hpp"

std::ostream& operator<<(std::ostream& os, const Neuron& neuron) {
    os << "Neuron Weights: [";
    for (size_t i = 0; i < neuron.weights->size(); i++) {
        os << (*neuron.weights)[i]; 
        if (i < neuron.weights->size() - 1) os << ", ";
    }
    os << "]\n";

    os << "Neuron input : [";

    for (size_t i = 0; i < neuron.input->size(); i++){
        os << (*neuron.input)[i];
        if (i < neuron.input->size() - 1) os << ", ";
    }
    os << "]\n";

    os << "Neuron output : ";
    os << (*neuron.output);
    os << "\n";

    os << "Neuron biais : ";
    os << (*neuron.biais);
    os << "\n";
    return os;
}


Neuron::Neuron(std::shared_ptr<const std::vector<float>> weights, std::shared_ptr<const std::vector<float>> input, std::shared_ptr<float> output, std::shared_ptr<const float> biais)
    : weights(weights), input(input), output(output), biais(biais)
{
    if (weights->size() != input->size()){
        throw std::invalid_argument( "NEURON COMPUTE_OUTPUT : The size of the vectors weights and input must be the same in a neuron" );
    }

    std::cout << "Neuron has been successfully created" << std::endl;
}

void Neuron::compute_output(){
    *output = 0.0f;
    for (size_t i = 0; i < weights->size(); i++){
        *output += (*weights)[i] * (*input)[i];
    }
    *output += *biais;
}