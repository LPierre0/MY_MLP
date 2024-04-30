#include "others/display.h"


NeuronVisualizer::NeuronVisualizer(int windowWidth, int windowHeight, network net) : window(sf::VideoMode(windowWidth, windowHeight), "Neuron Visualizer") {
    this->net = net;
    std::vector<std::vector<neurons>> layers = net.getNeuronsMatrix();
    s = "1";
    neuronsCircle.resize(layers.size());
    for (unsigned int i = 0; i < layers.size(); i++) {
        neuronsCircle[i].resize(layers[i].size());
    }
    text.resize(layers.size());
    for (unsigned int i = 0; i < layers.size(); i++) {
        text[i].resize(layers[i].size());
    }
    if (!font.loadFromFile("/usr/share/fonts/truetype/tlwg/TlwgTypo-Bold.ttf")) {
        std::cerr << "Erreur lors du chargement de la police par défaut de SFML" << std::endl;
    }
    st.push_back('A');
    unsigned int sizeGoal = layers[0][0].getValueInSize();
    for(unsigned int i = 0; i < sizeGoal; i++){
        in.resize(layers[0][0].getValueInSize());
        in[i].setFont(font);
        in[i].setCharacterSize(30);
        in[i].setString(st[i]);
        in[i].setFillColor(sf::Color::Black);
        sf::FloatRect textRect = in[i].getLocalBounds();
        in[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        in[i].setPosition(windowWidth / (layers.size() + 2), windowHeight / (layers[0][0].getValueInSize() + 1) * (i + 1));
        st.push_back(++st[i]);
    }

    for (unsigned int i = 0; i < layers.size(); i++){
        for(unsigned int j = 0; j < layers[i].size(); j++){
            neuronsCircle[i][j].setRadius(20);
            neuronsCircle[i][j].setFillColor(sf::Color::Transparent); 
            neuronsCircle[i][j].setOutlineThickness(2);
            neuronsCircle[i][j].setOutlineColor(sf::Color::Black);
            neuronsCircle[i][j].setPosition(windowWidth / (layers.size() + 2) * (i + 2) - neuronsCircle[i][j].getRadius(), windowHeight / (layers[i].size() + 1) * (j + 1) - neuronsCircle[i][j].getRadius());

            text[i][j].setFont(font);
            text[i][j].setCharacterSize(20); // Taille de caractère plus raisonnable
            text[i][j].setString(s);
            text[i][j].setFillColor(sf::Color::Black);

            sf::FloatRect textRect = text[i][j].getLocalBounds();
            text[i][j].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text[i][j].setPosition(neuronsCircle[i][j].getPosition().x + neuronsCircle[i][j].getRadius(), neuronsCircle[i][j].getPosition().y + neuronsCircle[i][j].getRadius());
            int value = std::stoi(s);
            ++value;
            s = std::to_string(value);
        }
    }

    for(unsigned int i = 0; i < in.size(); i++){
        for(unsigned int j = 0; j < layers[0].size(); j++){
            sf::Vector2f start(in[i].getPosition().x, in[i].getPosition().y);
            sf::Vector2f end(neuronsCircle[0][j].getPosition().x , neuronsCircle[0][j].getPosition().y + neuronsCircle[0][j].getRadius());
            lines.push_back(start);
            lines.push_back(end);
            weights.push_back(std::to_string(layers[0][j].getWeightIn()[i]));
        }
    }

    for (unsigned int i = 0; i < layers.size() - 1; i++) {
        for(unsigned int j = 0; j < layers[i].size(); j++) {
            for(unsigned int k = 0; k < layers[i+1].size(); k++) {
                sf::Vector2f start(neuronsCircle[i][j].getPosition().x + 2 * neuronsCircle[i][j].getRadius(), neuronsCircle[i][j].getPosition().y + neuronsCircle[i][j].getRadius());
                sf::Vector2f end(neuronsCircle[i+1][k].getPosition().x , neuronsCircle[i+1][k].getPosition().y + neuronsCircle[i+1][k].getRadius());
                lines.push_back(start);
                lines.push_back(end);
                weights.push_back(std::to_string(layers[i+1][k].getWeightIn()[j]));
            }
        }
    }
}


void NeuronVisualizer::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        std::vector<std::vector<neurons>> layers = net.getNeuronsMatrix();
        for (unsigned int i = 0; i < layers.size(); i++){
            for(unsigned int j = 0; j < layers[i].size(); j++){
                window.draw(neuronsCircle[i][j]);
                window.draw(text[i][j]);
            }
            for(unsigned int i = 0; i <layers[0][0].getValueInSize(); i++){
                window.draw(in[i]);
            }
        }
        for (unsigned int i = 0; i < lines.size() / 2; i += 1) {
            sf::Vertex line[] = {
                sf::Vertex(lines[i * 2], sf::Color::Blue),
                sf::Vertex(lines[i * 2 + 1], sf::Color::Blue)
            };
            sf::Vector2f middle((lines[i *2].x + lines[i *2+1].x) / 2.f, (lines[i * 2 + 1].y + lines[i *2].y)/2.f);
            sf::Text textWeight(weights[i], font, 15);
            textWeight.setFillColor(sf::Color::Red);
            sf::FloatRect textRect = textWeight.getLocalBounds();
            textWeight.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
            textWeight.setPosition(middle);
            //window.draw(textWeight);
            window.draw(line, 2, sf::Lines);

        }
        window.display();
    }
}


void display(network net) {
    NeuronVisualizer visualizer(800, 600, net);
    visualizer.run();
}
