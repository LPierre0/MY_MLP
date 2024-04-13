#ifndef INCLUDE_H
#define INCLUDE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

typedef struct data_s{
    std::vector<float> vectorizedImg;
    int label;
}data_t;

void printVectorFloat(std::vector<float> vec); 
void printVectorInt(std::vector<int> vec);
void test();
std::vector<unsigned int> shuffle(unsigned int size);
std::vector<float> vectorize(std::string path_image);
std::vector<data_t> getDataLabelled(std::vector<std::string> foldersName, std::string path_dataset);
#endif