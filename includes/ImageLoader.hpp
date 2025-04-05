#ifndef IMAGE_LOADER
#define IMAGE_LOADER

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>


class ImageLoader{
    public:
        ImageLoader(std::string filepath_images, std::string filepath_labels);
        std::vector<std::vector<uint8_t>> images;
        std::vector<uint8_t> labels;

    private:
        void load_images();
        void load_labels();
        std::string filepath_images;
        std::string filepath_labels;


};




#endif
