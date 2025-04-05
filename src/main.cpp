#include "Network.hpp"
#include "Function.hpp"
#include "ImageLoader.hpp"
#include <cmath>



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
    Network network(784, 2, 128, 10, 0.01);
    ImageLoader imload("../data/train-images-idx3-ubyte/train-images-idx3-ubyte", "../data/train-labels-idx1-ubyte/train-labels-idx1-ubyte");
    std::vector<std::vector<float>> images_cleaned = clean_images(imload.images);
    std::vector<std::vector<float>> labels_cleaned = clean_labels(imload.labels, 10);


    std::cout << "Training on " << imload.nb_images << " images." << std::endl;
    for (size_t i = 0; i < imload.nb_images; i++){
        network.forward(images_cleaned[i]);
        network.compute_backpropagation(labels_cleaned[i]);
    }

    ImageLoader imload_test("../data/t10k-images.idx3-ubyte", "../data/t10k-labels.idx1-ubyte");
    std::vector<std::vector<float>> images_cleaned_test = clean_images(imload_test.images);

    std::vector<float> true_pos(10, 0.0f);
    std::vector<float> false_pos(10, 0.0f);
    int predicted = 0;
    int true_value = 0;
    for (size_t i = 0; i < 10000; i++){
        network.forward(images_cleaned_test[i]);    
        predicted = network.get_predicted_value();
        true_value = (int)imload_test.labels[i];
        if (predicted == true_value){
            true_pos[predicted]++;
        }else{
            false_pos[predicted]++;
        }
    }


    float precision = 0.0f;

    for (int i = 0; i < 10; i++){
        precision += true_pos[i] / (true_pos[i] + false_pos[i]);    
    }
    precision = precision / 10.0;

    std::cout << "La precision du modèle est de : " << precision * 100 << "%" << std::endl; 
}




int main(){
    test_mnist();
}