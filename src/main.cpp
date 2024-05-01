#include "neural/neuron.h"
#include "neural/network.h"
#include "others/utils.h"
#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "others/display.h"

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






int main(){
    network net;
    net.createMlp();
    net.initWeights(100);
    std::vector temp(160000, 1.0f);
    net.forward(temp);
    std::vector tempy(151, 0.0f);
    tempy[1] = 1.0f;
    net.backward(tempy);
}
