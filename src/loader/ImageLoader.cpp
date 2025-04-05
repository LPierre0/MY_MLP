#include "ImageLoader.hpp"

ImageLoader::ImageLoader(std::string filepath_images, std::string filepath_labels)
    :filepath_images(filepath_images), filepath_labels(filepath_labels){
        this->load_images();
        this->load_labels();
}


void ImageLoader::load_images(){
    std::ifstream images_file(filepath_images, std::ios::binary);
    if (!images_file.is_open()){
        throw std::invalid_argument("[LOAD IMAGE] : Cannot open the file : " + filepath_images);
    }
    
    int32_t magic_number = 0, number_of_images = 0, rows = 0, cols = 0;
    images_file.read((char*)&magic_number, 4);
    images_file.read((char*)&number_of_images, 4);
    images_file.read((char*)&rows, 4);
    images_file.read((char*)&cols, 4);
    
    magic_number = __builtin_bswap32(magic_number);
    number_of_images = __builtin_bswap32(number_of_images);
    rows = __builtin_bswap32(rows);
    cols = __builtin_bswap32(cols);
    
    images = std::vector<std::vector<uint8_t>>(number_of_images, std::vector<uint8_t>(rows * cols));
    this->nb_images = (int)number_of_images;
    for (int i = 0; i < number_of_images; ++i)
    images_file.read((char*)images[i].data(), rows * cols);
    
    std::cout << "Successfully open the file : " << filepath_images << std::endl;
}

void ImageLoader::load_labels(){
    std::ifstream labels_file(filepath_labels, std::ios::binary);
    if (!labels_file){
        throw std::invalid_argument("[LOAD LABEL] : Cannot open the file : " + filepath_labels);
    }   

    int32_t magic_number = 0, number_of_items = 0;
    labels_file.read((char*)&magic_number, 4);
    labels_file.read((char*)&number_of_items, 4);

    magic_number = __builtin_bswap32(magic_number);
    number_of_items = __builtin_bswap32(number_of_items);

    labels = std::vector<uint8_t>(number_of_items);
    labels_file.read((char*)labels.data(), number_of_items);

}