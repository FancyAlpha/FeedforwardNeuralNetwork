//
// Created by tarak on 12/28/2019.
//

#include <iostream>
#include <ctime>
#include "Layer.h"

// w is size of this layer, h is size of next layer?
Layer::Layer(int width, int height, Randomizer *weightsRandomizer, Randomizer *biasRandomizer)
        : weights(width, height),
          biases(1, height) {

    if (weightsRandomizer != nullptr) biases.randomize(weightsRandomizer);
    if (biasRandomizer != nullptr) biases.randomize(biasRandomizer);
}

Matrix Layer::feedforward(const Matrix &activations) {
    return (weights * activations) + biases;
}

ostream &operator<<(ostream &os, const Layer &other) {

    os << "layer stats:" << endl;
    os << "weights " << other.weights.width() << "x" << other.weights.height() << endl;
    os << "weights " << other.biases.width() << "x" << other.biases.height() << endl;

    return os;
}
