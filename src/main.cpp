#include "Network.hpp"
#include "Function.hpp"
#include "ImageLoader.hpp"




void test_2_2_2_2(){
    Network network = Network(2, 1, 2, 2);
    std::vector<float> input = {1.0f, 2.0f};
    std::vector<float> true_vector = {1.0f, 0.0f};
    network.weights[0].set_value({0.1, 0.2, 0.3, 0.4});
    network.weights[1].set_value({0.1, 0.3, 0.2, 0.4});

    network.forward(input);

    std::cout << network << std::endl;
    network.compute_backpropagation(true_vector);
    std::cout << network.nabla_layer[0] << std::endl;
    std::cout << network.nabla_layer[1] << std::endl;

    std::cout << network << std::endl;

}


std::vector<std::vector<float>> clean_images(std::vector<std::vector<uint8_t>> images){
    float min = 0.0f;
    float max = 255.0f; 

    std::vector<std::vector<float>> images_cleaned;
    for (size_t l = 0; l < images.size(); l++){
        std::vector<float> temp(images[l].size(), 0.0f);
        for (size_t i = 0; i < images[l].size(); i++){
            temp[i] = (images[l][i] - min) / (max - min);
        }
        images_cleaned.push_back(temp);
    }
    return images_cleaned;
}


std::vector<std::vector<float>> clean_labels(std::vector<uint8_t> labels, int nb_labels){
    std::vector<std::vector<float>> labels_cleaned;

    for (size_t l = 0; l < labels.size(); l++){
        labels_cleaned.push_back(std::vector<float>(10, 0.0f));
        labels_cleaned[l][labels[l]] = 1.0f;
    }
    return labels_cleaned;
}

void test_mnist(){
    Network network(784, 5, 32, 10);
    ImageLoader imload("/home/pierre/Projects/MY_MLP/data/t10k-images.idx3-ubyte", "/home/pierre/Projects/MY_MLP/data/t10k-labels.idx1-ubyte");
    std::vector<std::vector<float>> images_cleaned = clean_images(imload.images);
    std::vector<std::vector<float>> labels_cleaned = clean_labels(imload.labels, 10);

    for (size_t i = 0; i < 1; i++){
        network.forward(images_cleaned[i]);
        network.compute_backpropagation(labels_cleaned[i]);
        std::cout << network << std::endl;
    }
}




int main(){
    test_mnist();
}