#ifndef PREPRO_H
#define PREPRO_H

#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "stb_image.h"
#include <vector>

typedef struct data_s{
    std::vector<float> vectorizedImg;
    int label;
}data_t;

int resize();
std::vector<float> vectorize(std::string path_image);
std::vector<data_t> getDataLabelled(std::vector<std::string> foldersName, std::string path_dataset);

#endif