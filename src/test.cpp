#include "Matrix.hpp"
#include "Function.hpp"
#include "ImageLoader.hpp"

float square(float x){
    return x * x;
}


int test_map(){
    Matrix m = Matrix(10, 10, 1.0f);
    for (size_t i = 0; i < m.matrix_nb_col() * m.matrix_nb_row(); i++){
        if (i % 2 == 0){
            m.my_matrix[i] = i;
        }else{
            m.my_matrix[i] = float(i)* -1;
        }
    }
    std::cout << m << std::endl;

    m = m.map(relu);

    std::cout << m << std::endl;
    return 0;
}

void save_mnist_pgm(const std::vector<uint8_t>& image, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    ofs << "P5\n28 28\n255\n";
    ofs.write(reinterpret_cast<const char*>(image.data()), image.size());
}

int main(){
    ImageLoader imload("/home/pierre/Projects/MY_MLP/data/t10k-images.idx3-ubyte", "/home/pierre/Projects/MY_MLP/data/t10k-labels.idx1-ubyte");
    for (int i = 0; i < 10; i++) {
        std::string filepath = "digit_" + std::to_string(i) +
                               "_lab" + std::to_string(static_cast<int>(imload.labels[i])) + ".pgm";
        save_mnist_pgm(imload.images[i], filepath);
    }
    return 0;
}