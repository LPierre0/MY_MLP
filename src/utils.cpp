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

std::vector<unsigned int> shuffle(unsigned int size){
    std::vector<unsigned int> indicesVec;
    for(unsigned int i = 0; i < size; i++){
        indicesVec.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indicesVec.begin(), indicesVec.end(), g);

    return indicesVec;
}