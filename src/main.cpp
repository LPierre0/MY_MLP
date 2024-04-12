#include "neural/neuron.h"
#include "others/utils.h"
#include "Preprocessing/preprocessing.h"

int main(){
    neurons perp;
    std::vector<std::vector<float>> in = {{3.0f, 2.0f, 1.0f}, {1.0f, 2.0f, 3.0f}, {3.0f, 1.0f, 3.0f}};
    std::vector<float> weightIn = {3.0f, 1.0f, 0.0f};
    std::vector<int> yTrain = {-1, -1, 1};
    perp.init(in[0], weightIn, 0.1f, PERCEPTRON);
    //perp.printSelf();
    perp.calculateOut();
    //perp.printSelf();
    perp.actualiseWeight(yTrain[0]);
    //perp.printSelf();
    test();
    resize();
    return 1;
}