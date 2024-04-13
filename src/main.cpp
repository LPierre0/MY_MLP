#include "neural/neuron.h"
#include "neural/network.h"
#include "others/utils.h"
#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

namespace fs = std::filesystem;
float nbPred = 0;
float nbPredSucces = 0;


void showImg(std::string pathImg, std::string predict, std::string ytrue) {
    cv::Mat image = cv::imread(pathImg, cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cerr << "Impossible de charger l'image !" << std::endl;
        return;
    }

    if (ytrue == predict) {
        nbPredSucces++;
    }
    nbPred++;

    // Afficher le texte "predict" en haut de l'image
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 1;
    int thickness = 4;
    cv::Point textOrg(10, 50); // Position du texte en haut à gauche
    cv::putText(image, predict, textOrg, fontFace, fontScale, cv::Scalar(255, 0, 0), thickness);

    // Afficher l'image
    cv::imshow("Image", image);
    cv::waitKey(2000); // Attendre 2 secondes (2000 ms) avant de fermer la fenêtre
}



void testPredict(std::vector<std::string> folders, neurons perp){
    std::string pathName = "/home/pierre//Documents/AI/TestCleaned/";
    std::string predict;
    for (const auto& folder : folders){
        for (const auto& entry : fs::recursive_directory_iterator(pathName + folder)){
            data_t temp;
            temp.vectorizedImg = vectorize(entry.path());
            int pred = perp.predict(temp.vectorizedImg);
            if (pred == 1){
                predict = "Pikachu";
            }else{
                predict = "Jigglypuff";
            }
            showImg(entry.path(), predict, folder);
        }
    }
}


int main(){
    std::vector<std::string> folder = {"Pikachu", "Jigglypuff"};

    std::vector<float> weightIn = {};
    std::vector<int> yTrain = {-1};
    std::vector<data_t> dataLabelled = getDataLabelled(folder, "/home/pierre/Documents/AI/DatasetCleaned/");
    neurons perp(dataLabelled[0].vectorizedImg.size(), 0.1f, PERCEPTRON);
    perp.train(dataLabelled);
    testPredict(folder, perp);

    std::cout << (nbPredSucces/nbPred) * 100 << "%" << std::endl;
    return 1;
}