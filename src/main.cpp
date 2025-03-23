#include "../includes/Neuron.hpp"

int main(){
    
    std::shared_ptr<std::vector<float>> weights(new std::vector<float>({0.1f, 0.2f, 0.3f}));
    std::shared_ptr<std::vector<float>> input(new std::vector<float>({1.0f, 2.0f, 3.0f}));
    std::shared_ptr<float> output(new float(0.0f));

    std::shared_ptr<float> biais(new float(0.1f));

    Neuron n(weights, input, output, biais);
    std::cout << n << std::endl;

    n.compute_output();

    std::cout << n << std::endl;

    std::cout << "OUTPUT : " << *output << std::endl;

    return 1;
}