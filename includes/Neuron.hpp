#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

class Neuron{
    public:
        Neuron(std::shared_ptr<const std::vector<float>> weights, std::shared_ptr<const std::vector<float>> input, std::shared_ptr<float> output, std::shared_ptr<const float> biais);

        friend std::ostream& operator<<(std::ostream& os, const Neuron& neuron); 

        void compute_output();
    

    private:
        std::shared_ptr<const std::vector<float>> weights;
        std::shared_ptr<const std::vector<float>> input;
        std::shared_ptr<float> output;
        std::shared_ptr<const float> biais;
};

#endif