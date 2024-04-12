#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "preprocessing.h"

namespace fs = std::filesystem;

int resize() {
    std::string path_newFile = "/home/pierre/Documents/AI/DatasetCleaned/";
    fs::remove_all(path_newFile); // Supprimer et recréer le dossier de destination
    fs::create_directories(path_newFile);

    std::string path_dataset = "/home/pierre/Documents/AI/FirstNeuralNetwork/dataset";

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
