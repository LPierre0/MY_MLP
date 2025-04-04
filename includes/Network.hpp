#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include "Matrix.hpp"
#include "Function.hpp"


class Network{

    public:
        Network(size_t input_size, size_t nb_hidden_layer, size_t nb_neurons, size_t output_size);
        friend std::ostream& operator<<(std::ostream& os, const Network& network); 

        void forward(std::vector<float> in);
        void set_weights(std::vector<float> w, size_t indice);
        void save(std::string file_path);
        void load(std::string file_path);
        void compute_backpropagation(Matrix y_true);


        Matrix get_softmaxed_output();
        
        size_t input_size;
        size_t nb_hidden_layer;
        size_t nb_neurons;
        size_t output_size;

        std::vector<Matrix> weights;
        std::vector<Matrix> biais;
        std::vector<Matrix> pre_activation_layer;
        std::vector<Matrix> activated_layer;
        std::vector<Matrix> nabla_layer;
        Matrix output;
        Matrix softmaxed_output;
        Matrix input;
        

    private:





};

#endif