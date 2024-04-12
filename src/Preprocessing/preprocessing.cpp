#include "others/preprocessing.h"


namespace fs = std::filesystem;

int resize() {
    std::string path_newFile = "/home/pierre/Documents/AI/TestCleaned/";
    fs::remove_all(path_newFile); // Supprimer et recréer le dossier de destination
    fs::create_directories(path_newFile);

    std::string path_dataset = "/home/pierre/Documents/AI/TestPikachujiggi";

    for (const auto& entry : fs::recursive_directory_iterator(path_dataset)) {
        if (entry.is_regular_file()) {
            std::string file = entry.path().filename();
            std::string extension = entry.path().extension();
            // Vérifier si le fichier est une image JPG ou PNG
            if (extension == ".jpg" || extension == ".jpeg" || extension == ".png") {
                try {
                    // Charger l'image
                    cv::Mat img = cv::imread(entry.path(), cv::IMREAD_COLOR);

                    // Redimensionner l'image
                    cv::Mat resize_img;
                    cv::resize(img, resize_img, cv::Size(800, 800), 0, 0, cv::INTER_LINEAR);

                    // Déterminer le dossier de destination
                    fs::path dest_folder = fs::path(path_newFile) / entry.path().parent_path().filename();
                    
                    // Créer le dossier de destination si nécessaire
                    fs::create_directories(dest_folder);

                    // Enregistrer l'image redimensionnée
                    std::string dest_file = (dest_folder / file).string();
                    cv::imwrite(dest_file, resize_img);

                } catch (const std::exception& e) {
                    //std::cerr << "Erreur lors du traitement de l'image " << file << ": " << e.what() << std::endl;
                }
            }
        }
    }
    return 0;
}

/*
void test(){
    std::string filepath = "/home/pierre/Documents/AI/FirstNeuralNetwork/data/pikachu/best-pickachu-nicknames.jpeg";
    int width, height, channels;

    // Lire l'image
    unsigned char* image = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    if (!image) {
        std::cerr << "Erreur lors du chargement de l'image " << filepath << std::endl;
        return;
    }

    // Afficher les valeurs des pixels
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Calculer l'indice du pixel dans le tableau de données de l'image
            int pixelIndex = (y * width + x) * channels;

            // Afficher les valeurs RVB (ou RGBA si channels = 4)
            std::cout << "Pixel (" << x << ", " << y << "): ";
            for (int c = 0; c < channels; ++c) {
                std::cout << static_cast<int>(image[pixelIndex + c]) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Libérer la mémoire allouée pour l'image
    stbi_image_free(image);
}
*/



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
    std::vector<data_t> dataLabelled;
    for (const auto& folderName : foldersName){
        for (const auto& entry : fs::recursive_directory_iterator(path_dataset + folderName)){
            data_t temp;
            temp.vectorizedImg = vectorize(entry.path());
            if (folderName == "Pikachu"){
                temp.label = 1;
            }else{
                temp.label = -1;
            }
            dataLabelled.push_back(temp);
        }
    }
    return dataLabelled;
}
