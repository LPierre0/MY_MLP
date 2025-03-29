#include "Network.hpp"

int main(){
    Network network = Network(2, 3, 3, 2);
    std::cout << network << std::endl;

    network.forward({1.0f, -2.0f});

    std::cout << "--------FORWARD------------\n\n" << std::endl;
    std::cout << network << std::endl;

}