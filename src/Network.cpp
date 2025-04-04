#include "Network.hpp"


Network::Network(size_t input_size, size_t nb_hidden_layer, size_t nb_neurons, size_t output_size)
:input_size(input_size), nb_hidden_layer(nb_hidden_layer), nb_neurons(nb_neurons), output_size(output_size){
    weights.push_back(he_weights_init(nb_neurons, input_size));
    biais.push_back(Matrix(nb_neurons, 1, 0.0f));
    input = Matrix(input_size, 1, 0.0f);
    nabla_layer.push_back(Matrix(input_size, 1, 0.0f));

    for (size_t i = 0; i < nb_hidden_layer - 1; i++){
        weights.push_back(he_weights_init(nb_neurons, nb_neurons));
        biais.push_back(Matrix(nb_neurons, 1, 0.0f));
    }
    
    for (size_t i = 0; i < nb_hidden_layer; i++){
        nabla_layer.push_back(Matrix(nb_neurons, 1, 0.0f));
        pre_activation_layer.push_back(Matrix(nb_neurons, 1, 0.0f));
        activated_layer.push_back(Matrix(nb_neurons, 1, 0.0f));
    }
    nabla_layer.push_back(Matrix(output_size, 1, 0.0f));

    weights.push_back(he_weights_init(output_size, nb_neurons));
    biais.push_back(Matrix(output_size, 1, 0.0f)); 
    output = Matrix(output_size, 1, 0.0f);
    softmaxed_output = Matrix(output_size, 1, 0.0f);
}


std::ostream& operator<<(std::ostream& os, const Network& network)
{

    os << "input size : " << network.input_size << " nb hidden layer : " << network.nb_hidden_layer;
    os << " nb neurons : " << network.nb_hidden_layer << " output size : " << network.output_size;
    os << "\n";

    os << "input \n" << network.input << "\n";


    os << "weights : \n";
    int i = 0;
    for (auto& matrix : network.weights){
        os << "Layer " << ++i << "\n";

        os << matrix;
        os << "----------------------------\n";
    }
    os << "biais : \n";
    i = 0;
    for (auto& matrix : network.biais){
        os << "Layer " << ++i << "\n";
        os << matrix;
        os << "----------------------------\n";
    }

    i = 0;
    os << "Preactivation layer : \n";
    for (auto& matrix : network.pre_activation_layer){
        os << "Layer " << ++i << "\n";
        os << matrix;
        os << "----------------------------\n";
    }

    i = 0;
    os << "activated layer : \n";
    for (auto& matrix : network.activated_layer){
        os << "Layer " << ++i << "\n";
        os << matrix;
        os << "----------------------------\n";
    }

    os << "output : \n" << network.output << "\n";


    os << "softmaxed output : \n" << network.softmaxed_output << "\n"; 
    return os;
}


void Network::forward(std::vector<float> in){
    input.set_value(in);

    pre_activation_layer[0] = weights[0] * input + biais[0];
    activated_layer[0] = pre_activation_layer[0].map(relu);
    for (size_t i = 1; i < pre_activation_layer.size(); i++){
        std::cout << i << std::endl;
        pre_activation_layer[i] =  weights[i] * activated_layer[i - 1] + biais[i];
        activated_layer[i] = pre_activation_layer[i].map(relu);
    }
    output = weights[weights.size() - 1] * activated_layer[activated_layer.size() - 1] + biais[biais.size() - 1];
    softmaxed_output = output.map(my_exp);
    softmaxed_output = softmaxed_output / softmaxed_output.sum();
}


void Network::set_weights(std::vector<float> w, size_t indice){
    weights[indice].set_value(w);
}




void Network::save(std::string file_path){
    std::ofstream file(file_path, std::ios::binary);
    if (!file) throw std::runtime_error("Impossible d'ouvrir le fichier");

    file.write(reinterpret_cast<char*>(&input_size), sizeof(input_size));
    file.write(reinterpret_cast<char*>(&nb_hidden_layer), sizeof(nb_hidden_layer));
    file.write(reinterpret_cast<char*>(&nb_neurons), sizeof(nb_neurons));
    file.write(reinterpret_cast<char*>(&output_size), sizeof(output_size));

    for (const auto& layer : weights) {
        size_t size = layer.my_matrix.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        file.write(reinterpret_cast<const char*>(layer.my_matrix.data()), size * sizeof(float));
    }

    for (const auto& layer : biais) {
        size_t size = layer.my_matrix.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        file.write(reinterpret_cast<const char*>(layer.my_matrix.data()), size * sizeof(float));
    }

    file.close();
}

void Network::load(std::string file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) throw std::runtime_error("Impossible d'ouvrir le fichier");

    // Lecture des métadonnées
    file.read(reinterpret_cast<char*>(&input_size), sizeof(input_size));
    file.read(reinterpret_cast<char*>(&nb_hidden_layer), sizeof(nb_hidden_layer));
    file.read(reinterpret_cast<char*>(&nb_neurons), sizeof(nb_neurons));
    file.read(reinterpret_cast<char*>(&output_size), sizeof(output_size));

    // Lecture des layers
    weights.resize(nb_hidden_layer + 1);
    for (auto& layer : weights) {
        size_t size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        layer.my_matrix.resize(size);
        file.read(reinterpret_cast<char*>(layer.my_matrix.data()), size * sizeof(float));
    }

    biais.resize(nb_hidden_layer + 1);
    for (auto& layer : biais) {
        size_t size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        layer.my_matrix.resize(size);
        file.read(reinterpret_cast<char*>(layer.my_matrix.data()), size * sizeof(float));  
    }


    file.close();
}



Matrix Network::get_softmaxed_output(){
    return this->softmaxed_output;
}

void Network::compute_backpropagation(Matrix y_true){
    size_t nb_layer = this->nabla_layer.size();
    this->nabla_layer[nb_layer - 1] = cross_entropy_derivative(this->softmaxed_output, y_true);

    for (size_t l = nb_layer - 2; l > 0; l--){
        std::cout << l << std::endl;
        std::cout << this->nabla_layer[l+1].matrix_nb_row() << "," << this->nabla_layer[l+1].matrix_nb_col() << std::endl;
        std::cout << this->pre_activation_layer[l-1] << std::endl;
        std::cout << this->weights[l].transpose() << std::endl;

        this->nabla_layer[l] = (this->weights[l].transpose() * this->nabla_layer[l+1]).hadamard(relu_derivate(this->pre_activation_layer[l-1]));
    }
    this->nabla_layer[0] = (this->weights[0].transpose() * this->nabla_layer[1]).hadamard(relu_derivate(this->input));
}