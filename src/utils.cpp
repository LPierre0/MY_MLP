#include "others/utils.h"
#include "stb_image.h"
#include <vector>
#include <algorithm>
#include <random>


using namespace std;

void printVectorFloat(vector<float> vec){
    for (unsigned int i = 0; i < vec.size() - 1; i++){
        cout << vec[i] << ",";
    }
    cout << vec[(vec.size() - 1)] << endl;
}

void printVectorInt(std::vector<int> vec){
    for (unsigned int i = 0; i < vec.size() - 1; i++){
        cout << vec[i] << ",";
    }
    cout << vec[(vec.size() - 1)] << endl;
}

std::vector<unsigned int> createShuffledIndices(unsigned int size){
    std::vector<unsigned int> indicesVec;

    for(unsigned int i = 0; i < size; i++){
        indicesVec.push_back(i);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indicesVec.begin(), indicesVec.end(), g);
    return indicesVec;
}


// TODO: Paralléliser.

std::vector<float> vectorize(std::string path_image){
    int width, height, channels;
    unsigned char * image = stbi_load(path_image.c_str(), &width, &height, &channels, 0);
    if (!image){
        std::cerr << "Erreur when loading the image" << path_image << std::endl;
    }
    std::vector<float> vectorizedImage;
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            int pixelIndex = (y * width + x) * channels;
            for(int c = 0; c < channels; ++c){
                vectorizedImage.push_back(static_cast<float>(image[pixelIndex + c]));
            }
        }
    }
    return vectorizedImage;
}




std::vector<data_t> getDataLabelled(std::vector<std::string> foldersName, std::string path_dataset){
    namespace fs = std::filesystem;
    std::vector<data_t> dataLabelled;
    for (const auto& folderName : foldersName){
        for (const auto& img : fs::recursive_directory_iterator(path_dataset + folderName)){
            data_t temp;
            temp.vectorizedImg = vectorize(img.path());
            if (folderName == "Charmander"){
                temp.label = 1;
            }else{
                temp.label = -1;
            }
            dataLabelled.push_back(temp);
        }
    }
    return dataLabelled;
}
