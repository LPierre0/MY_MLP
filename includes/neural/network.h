#ifndef NETWORK_H
#define NETWORK_H

#include "neural/neuron.h"
#include <vector>
#include <iostream>
#include <filesystem>

class network {
    public : 
        std::vector<neurons> net;
        void train(std::vector<std::string> foldersName, std::string path_dataset);

};


#endif