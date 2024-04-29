#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "neural/network.h"
#include "neural/neuron.h"

class NeuronVisualizer {
public:
    NeuronVisualizer(int windowWidth, int windowHeight, network net);
    void run();

private:
    sf::RenderWindow window;
    std::vector<std::vector<sf::CircleShape>> neuronsCircle;
    sf::Font font;
    std::vector<std::vector<sf::Text>> text;
    std::string s;
    std::vector<sf::Vector2f> lines;
    std::vector<std::string> weights;
    std::vector<sf::Text> in;
    std::vector<char> st;
    network net;
};

void display(network net);

#endif