#include "others/utils.h"
#include "stb_image.h"

using namespace std;

void printVectorFloat(vector<float> vec){
    for (unsigned int i = 0; i < vec.size() - 1; i++){
        cout << vec[i] << ",";
    }
    cout << vec[(vec.size() - 1)] << endl;
}

void printVectorInt(std::vector<int> vec){
    for (unsigned int i = 0; i < vec.size() - 1; i++){
        cout << vec[i] << ",";
    }
    cout << vec[(vec.size() - 1)] << endl;
}

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