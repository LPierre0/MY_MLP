#include "others/preprocessing.h"


namespace fs = std::filesystem;

void resizeImage(std::filesystem::directory_entry entry, std::string pathNewFolder, int newWidht, int newHeight){
    if (entry.is_regular_file()) {
        std::string file = entry.path().filename();
        std::string extension = entry.path().extension();
        if (extension == ".jpg" || extension == ".jpeg" || extension == ".png") {
            try {
                cv::Mat img = cv::imread(entry.path(), cv::IMREAD_COLOR);
                cv::Mat resize_img;
                cv::resize(img, resize_img, cv::Size(newWidht, newHeight), 0, 0, cv::INTER_LINEAR);
                fs::path dest_folder = fs::path(pathNewFolder) / entry.path().parent_path().filename();
                fs::create_directories(dest_folder);
                std::string dest_file = (dest_folder / file).string();
                cv::imwrite(dest_file, resize_img);

            } catch (const std::exception& e) {
                std::cerr << "Error with image treatment" << file << ": " << e.what() << std::endl;
            }
        }
    }
}



void resizeFolder(std::string pathFolderToResize, std::string pathNewFolder, int newWidht, int newHeight){

    fs::remove_all(pathNewFolder); 
    fs::create_directories(pathNewFolder);

    for (const auto& entry : fs::recursive_directory_iterator(pathFolderToResize)) {
        if (entry.is_regular_file()) {
            std::string file = entry.path().filename();
            std::string extension = entry.path().extension();
            resizeImage(entry, pathNewFolder, newWidht, newHeight);
        }
    }
}


int main(int argc, char * argv[]){
    if (argc != 5){
        std::cerr << "Incorrect usage, usage : ./prediction FolderToResizePath NewFolderPath newWidht newHeight" << std::endl;
        return 1;
    }
    std::string pathFolderToResize = argv[1];
    std::string pathNewFolder = argv[2];
    int newWidth = std::stoi(argv[3]);
    int newHeight = std::stoi(argv[4]);

    if(newWidth < 0){
        std::cerr << "Error with widht dimension, actual dimension" << newWidth << std::endl;
        return 1;
    }
    if(newHeight < 0){
        std::cerr << "Error with widht dimension, actual dimension" << newHeight << std::endl;
        return 1;
    }
    if (!std::filesystem::exists(pathFolderToResize)) {
        std::cerr << "The directory " << pathFolderToResize << " does not exist." << std::endl;
        return 1; // Quitte le programme avec un code d'erreur
    }

    std::cout << "Resizing has started" << std::endl;
    resizeFolder(pathFolderToResize, pathNewFolder, newWidth, newHeight);
    return 0;
}
