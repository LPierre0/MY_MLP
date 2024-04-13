#ifndef PREPRO_H
#define PREPRO_H

#include <iostream>
#include <filesystem>
#include <vector>
#include <opencv2/opencv.hpp>
#include "stb_image.h"

void resizeFolder(std::string pathFolderToResize, std::string pathNewFolder, int newWidht, int newHeight);

#endif