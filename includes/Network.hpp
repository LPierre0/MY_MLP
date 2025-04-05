#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include "Matrix.hpp"
#include "Function.hpp"


class Network{

    public:
        Network(size_t input_size, size_t nb_hidden_layer, size_t nb_neurons, size_t output_size, float learning_rate = 0.01f);
        friend std::ostream& operator<<(std::ostream& os, const Network& network); 

        void forward(std::vector<float> in);
        void set_weights(std::vector<float> w, size_t indice);
        void save(std::string file_path);
        void load(std::string file_path);
        void compute_backpropagation(std::vector<float> y_true_vector);


        Matrix get_softmaxed_output();
        

        float learning_rate;
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
        Matrix y_true;
        

    private:





};

#endif